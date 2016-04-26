package lime.audio;


import haxe.io.Bytes;
import haxe.Timer;
import lime.app.Event;
import lime.audio.openal.AL;
import lime.system.System;
import lime.utils.AnonBytes;
import lime.utils.BytesUtil;
import lime.utils.UInt8Array;

#if flash
import flash.media.SoundChannel;
#elseif lime_console
import lime.audio.fmod.FMODChannel;
#end

#if lime_console
// TODO(james4k): this is terribly hacky. looking for more sane solutions.  the
// caller uses an extern declaration of this function so that it does not need
// to include haxe dependencies, but that's not really the hacky part. need a
// good way to export a c++ callable haxe function.
@:cppNamespaceCode("
void haxe_staticfunc_onFmodChannelEnd (ConsoleFmodChannel c) {
	AudioSource_obj::onFmodChannelEnd (c);
}
")
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


class AudioSource {
	
	
	public var onComplete = new Event<Void->Void> ();
	
	public var buffer:AudioBuffer;
	public var currentTime (get, set):Int;
	public var gain (get, set):Float;
	public var length (get, set):Int;
	public var loops (get, set):Int;
	public var offset:Int;

	private var id:UInt;
	private var playing:Bool;
	private var pauseTime:Int;
	private var __length:Null<Int>;
	private var __loops:Int;
	
	#if flash
	private var channel:SoundChannel;
	#elseif lime_console
	private var channel:FMODChannel;
	#end
	
	#if (cpp || neko || nodejs)
	private var queueTimer:Timer;
	private var format:Int;
	
	private var streamBuffers:Array<Int>;
	private var audioSamples:UInt8Array;
	private var bufferTime:Int;
	private var finishedDecoding:Bool;
	
	inline private static var initialBufferCount = 2;
	inline private static var minimumBufferTime:Int = 500;
	#end
	
	
	public function new (buffer:AudioBuffer = null, offset:Int = 0, length:Null<Int> = null, loops:Int = 0) {
		
		this.buffer = buffer;
		this.offset = offset;
		
		if (length != null && length != 0) {
			
			this.length = length;
			
		}
		
		this.loops = loops;
		id = 0;
		playing = false;
		bufferTime = 1000;
		finishedDecoding = false;
		
		if (buffer != null) {
			
			init ();
			
		}
		
	}

	
	public function dispose ():Void {
		
		switch (AudioManager.context) {
			
			case OPENAL (alc, al):
						
				#if (cpp || neko || nodejs)
				
				if (id != 0) {
					
					al.deleteSource (id);
					
				}
				
				if (buffer.stream && streamBuffers != null) {
					
					AL.deleteBuffers (streamBuffers);
					
				}
				
				#end
			
			default:
				
		}
		
	}
	
	
	private function init ():Void {
		
		switch (AudioManager.context) {
			
			case OPENAL (alc, al):
				
				#if (cpp || neko || nodejs)
				
				if (buffer.id == 0) {
					
					format = 0;
					
					if (buffer.channels == 1) {
						
						if (buffer.bitsPerSample == 8) {
							
							format = al.FORMAT_MONO8;
							
						} else if (buffer.bitsPerSample == 16) {
							
							format = al.FORMAT_MONO16;
							
						}
						
					} else if (buffer.channels == 2) {
						
						if (buffer.bitsPerSample == 8) {
							
							format = al.FORMAT_STEREO8;
							
						} else if (buffer.bitsPerSample == 16) {
							
							format = al.FORMAT_STEREO16;
							
						}
						
					}
					
					if (!buffer.stream) {
						
						buffer.id = al.genBuffer ();
						al.bufferData (buffer.id, format, buffer.data, buffer.data.length, buffer.sampleRate);
						
					}
					
				}
				
				id = al.genSource ();
				
				#end
			
			default:
			
		}
		
	}
	
	
	public function play ():Void {
		
		#if html5
		#elseif flash
		
		if (channel != null) channel.stop ();
		var channel = buffer.src.play (pauseTime / 1000);
		
		#elseif lime_console
		
		if (channel.valid) {
			
			channel.resume ();
			
		} else {
			
			channel = buffer.src.play ();
			channel.setLoopCount (this.__loops);
			
			var old = setFmodActive (channel, this);
			
			if (old != this) {
				
				old.channel = FMODChannel.INVALID;
				
			}
			
		}
		
		#else
		
		if (playing || id == 0) {
			
			return;
			
		}
		
		if (queueTimer != null) {
			
			queueTimer.stop ();
			queueTimer = null;
			
		}
		
		playing = true;
		queueTimer = new Timer (1);
		
		if (!buffer.stream) {
			
			queueTimer.run = timer_onRun;
			timer_onRun ();
			
		} else {
			
			queueTimer.run = streamTimer_onRun;
			streamTimer_onRun ();
			
		}
		
		AL.sourcePlay (id);
		
		#end
		
	}
	
	
	public function pause ():Void {
		
		#if html5
		#elseif flash
		
		if (channel != null) {
			
			pauseTime = Std.int (channel.position * 1000);
			channel.stop ();
			
		}
		
		#elseif lime_console
		
		if (channel.valid) {
			
			channel.pause ();
			
		}
		
		#else
		
		playing = false;
		AL.sourcePause (id);
		
		#end
		
	}
	
	
	public function stop ():Void {
		
		#if html5
		#elseif flash
		
		pauseTime = 0;
		
		if (channel != null) {
			
			channel.stop ();
			
		}
		
		#elseif lime_console
		
		if (channel.valid) {
			
			channel.stop ();
			
		}
		
		#else
		
		playing = false;
		AL.sourceStop (id);
		dispose ();
		id = 0;
		streamBuffers = null;
		
		#end
		
	}
	
	
	#if lime_console
	
	// TODO(james4k): these arrays become Array<Dynamic> so a lot of hidden
	// boxing and allocations going on.
	
	// can't use Maps because we need by-value key comparisons, so use two arrays.
	private static var fmodActiveChannels = new Array<FMODChannel> ();
	private static var fmodActiveSources = new Array<AudioSource> ();
	
	
	// onFmodChannelEnd is called from C++ when an fmod channel end callback is
	// called.
	private static function onFmodChannelEnd (channel:FMODChannel) {
		
		var source = removeFmodActive (channel);
		
		if (source != null) {
			
			source.channel = FMODChannel.INVALID;
			source.onComplete.dispatch ();
			
		}
		
	}
	
	
	// removeFmodActive disassociates an FMODChannel with its AudioSource, returning
	// the AudioSource it was associated with.
	private static function removeFmodActive(key:FMODChannel):AudioSource {
		
		for (i in 0...fmodActiveChannels.length) {
			
			if (fmodActiveChannels[i] == key) {
				
				var source = fmodActiveSources[i];
				
				// swap in the last element and pop() to remove from array
				var last = fmodActiveChannels.length - 1;
				fmodActiveChannels[i] = fmodActiveChannels[last];
				fmodActiveSources[i] = fmodActiveSources[last];
				
				fmodActiveChannels.pop ();
				fmodActiveSources.pop ();
				
				return source;
				
			}
			
		}
		
		return null;
		
	}
	
	
	// setFmodActive associates an FMODChannel with an AudioSource to allow for fmod
	// channel callbacks to propagate to the user's AudioSource onComplete
	// callbacks. Returns the previous AudioSource associated with the channel
	// if there was one, or the passed in AudioSource if not.
	private static function setFmodActive (key:FMODChannel, value:AudioSource):AudioSource {
		
		for (i in 0...fmodActiveChannels.length) {
			
			if (fmodActiveChannels[i] == key) {
				
				var old = fmodActiveSources[i];
				fmodActiveSources[i] = value;
				return old;
				
			}
			
		}
		
		fmodActiveChannels.push (key);
		fmodActiveSources.push (value);
		return value;
		
	}
	
	#end
	
	
	
	
	// Event Handlers
	
	
	
	
	private function timer_onRun ():Void {
		
		#if (cpp || neko || nodejs)
		
		var sourceState:Int = AL.getSourcei (id, AL.SOURCE_STATE);
		if (playing && !finishedDecoding)  {
			
			var buffers:Array<Int>;
			var bufferCount:Int;
			if (streamBuffers == null) {
				
				var minimalBufferCount:Int = getMinimalBufferCountForLoop ();
				bufferCount = (loops + 1) < minimalBufferCount ? (loops + 1) : minimalBufferCount;
				buffers = [];
				
			} else {
				
				bufferCount = AL.getSourcei (id, AL.BUFFERS_PROCESSED);
				
				if (bufferCount == 0) {
					
					return;
					
				}
				
				buffers = AL.sourceUnqueueBuffers (id, bufferCount);
				
			}
			
			for (i in 0 ... bufferCount) {
				
				buffers[i] = buffer.id;
				
			}
			
			AL.sourceQueueBuffers (id, bufferCount, buffers);
			loops -= bufferCount;
			
			if (loops < 0) {
				
				finishedDecoding = true;
				loops = 0;
				
			}
			
		} else if (!playing || sourceState == AL.STOPPED) {
			
			queueTimer.stop ();
			queueTimer = null;
			playing = false;
			dispose ();
			id = 0;
			streamBuffers = null;
			
		}
		
		#end
		
	}
	
	
	private function streamTimer_onRun () {
		
		#if (cpp || neko || nodejs)
		
		var sourceState:Int = AL.getSourcei (id, AL.SOURCE_STATE);
		if (playing && !finishedDecoding) {
			
			var bufferCount:Int;
			var buffers:Array<Int>;
			
			if (streamBuffers == null) {
				
				bufferCount = length < minimumBufferTime ? 1 : initialBufferCount;
				buffers = streamBuffers = AL.genBuffers (bufferCount);
				
			} else {
				
				bufferCount = AL.getSourcei (id, AL.BUFFERS_PROCESSED);
				
				if (bufferCount == 0) {
					
					return;
					
				}
				
				buffers = AL.sourceUnqueueBuffers (id, bufferCount);
				
			}
			
			var bufferSize:Int = getBufferSize ();
			
			if (audioSamples == null) {
				
				audioSamples = new UInt8Array (bufferSize);
				
			}
			
			var validBufferCount:Int = 0;
			
			var i:Int = 0;
			var writeOffset:Int = 0;
			while (i < bufferCount) {
				
				var numSamples:Int = lime_audio_stream_decode (buffer.handle, BytesUtil.getAnonBytesFromTypedArray (audioSamples), bufferSize, writeOffset);
				
				if (numSamples != 0) {
					
					AL.bufferData (buffers[i], format, audioSamples, numSamples, buffer.sampleRate);
					++validBufferCount;
					
					if (numSamples < bufferSize) {
						
						if (loops >= 1) {
							
							currentTime = 0;
							--loops;
							writeOffset = numSamples;
							continue;
							
						}
						
					} else {
						
						writeOffset = 0;
						
					}
					
				} else {
					
					if (loops >= 1) {
						
						currentTime = 0;
						--loops;
						continue;
						
					} else {
						
						finishedDecoding = true;
						
					}
					
					break;
					
				}
				
				++i;
			
			}
			
			if (validBufferCount != 0) {
				
				AL.sourceQueueBuffers (id, validBufferCount, buffers);
				
			} else {
				
				finishedDecoding = true;
				
			}
			
			if (sourceState == AL.STOPPED) {
				
				AL.sourcePlay (id);
				
			}
			
		} else if (!playing || sourceState == AL.STOPPED)  {
			
			queueTimer.stop ();
			queueTimer = null;
			playing = false;
			dispose ();
			id = 0;
			streamBuffers = null;
			
		}
		
		#end
		
	}
	
	
	// Get & Set Methods
	
	
	
	
	private function get_currentTime ():Int {
		
		#if html5
		
		return 0;
		
		#elseif flash
		
		return Std.int (channel.position);

		#elseif lime_console

		lime.Lib.notImplemented ("AudioSource.get_currentTime");
		return 0;
		
		#else
		
		var time = Std.int (AL.getSourcef (id, AL.SEC_OFFSET) * 1000) - offset;
		if (time < 0) return 0;
		return time;
		
		#end
		
	}
	
	
	private function set_currentTime (value:Int):Int {
		
		#if html5
		
		return pauseTime = value;
		
		#elseif flash
		
		// TODO: create new sound channel
		//channel.position = value;
		return pauseTime = value;

		#elseif lime_console

		lime.Lib.notImplemented ("AudioSource.set_currentTime");
		return value;
		
		#else
		
		finishedDecoding = false;
		if (buffer != null) {
			
			if (!buffer.stream) {
				
				AL.sourcef (id, AL.SEC_OFFSET, (value + offset) / 1000);
				
			} else {
				
				lime_audio_stream_seek (buffer.handle, value / 1000);
				
			}
			
		}
		
		return value;
		
		#end
		
	}
	
	
	private function get_gain ():Float {
		
		#if html5
		
		return 1;
		
		#elseif flash
		
		return channel.soundTransform.volume;

		#elseif lime_console

		lime.Lib.notImplemented ("AudioSource.get_gain");
		return 1;
		
		#else
		
		return AL.getSourcef (id, AL.GAIN);
		
		#end
		
	}
	
	
	private function set_gain (value:Float):Float {
		
		#if html5
		
		return 1;
		
		#elseif flash
		
		var soundTransform = channel.soundTransform;
		soundTransform.volume = value;
		channel.soundTransform = soundTransform;
		return value;

		#elseif lime_console

		lime.Lib.notImplemented ("AudioSource.set_gain");
		return value;
		
		#else
		
		AL.sourcef (id, AL.GAIN, value);
		return value;
		
		#end
		
	}
	
	
	private function get_length ():Int {
		
		if (__length != null) {
			
			return __length;
			
		}
		
		#if html5
		
		return 0;
		
		#elseif flash
		
		return Std.int (buffer.src.length);

		#elseif lime_console

		lime.Lib.notImplemented ("AudioSource.get_length");
		return 0;
		
		#else
		
		var samples = (buffer.length * 8) / (buffer.channels * buffer.bitsPerSample);
		return Std.int (samples / buffer.sampleRate * 1000) - offset;
		
		#end
		
	}
	
	
	private function set_length (value:Int):Int {
		
		#if lime_console

		lime.Lib.notImplemented ("AudioSource.set_length");
		return value;

		#elseif (!flash && !html5)
		#end
		
		return __length = value;
		
	}
	
	
	private function get_loops ():Int {
		
		#if lime_console
		
		if (channel.valid) {
			
			__loops = channel.getLoopCount ();
			
		}
		
		#end
		
		return __loops;
		
	}
	
	
	private function set_loops (loops:Int):Int {
		
		#if lime_console
		
		if (channel.valid) {
			
			channel.setLoopCount (loops);
			
		}
		
		#end
		
		return __loops = loops;
		
	}
	
	private function getBufferSize ():Int {
		
		return Std.int (buffer.sampleRate * buffer.bitsPerSample / 8 * buffer.channels * Math.max (bufferTime, minimumBufferTime) / 1000 / streamBuffers.length);
		
	}
	
	private function getMinimalBufferCountForLoop ():Int {
		
		return Std.int (Math.max (Math.floor (minimumBufferTime / length), 2));
		
	}
	
	#if (cpp || neko || nodejs)
	@:cffi private static function lime_audio_stream_decode (handle:Dynamic, data:Dynamic, readSize:Int, writeOffset:Int):Int;
	@:cffi private static function lime_audio_stream_seek (data:Dynamic, seconds:Float):Bool;
	#end
}
