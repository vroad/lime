package lime.audio;


import haxe.Timer;
import lime.app.Event;
import lime.audio.openal.AL;
import lime.system.System;
import lime.utils.ByteArray;

#if flash
import flash.media.SoundChannel;
#end


class AudioSource {
	
	
	public var onComplete = new Event<Void->Void> ();
	
	public var buffer:AudioBuffer;
	public var currentTime (get, set):Int;
	public var gain (get, set):Float;
	public var length (get, set):Int;
	public var loops:Int;
	public var offset:Int;
	
	private var id:UInt;
	private var playing:Bool;
	private var pauseTime:Int;
	private var __length:Null<Int>;
	
	#if flash
	private var channel:SoundChannel;
	#end
	
	#if (cpp || neko || nodejs)
	private var timer:Timer;
	private var queueTimer:Timer;
	private var format:Int;

	inline private static var initialBufferCount = 2;
	private var streamBuffers:Array<Int>;
	#end
	
	
	public function new (buffer:AudioBuffer = null, offset:Int = 0, length:Null<Int> = null, loops:Int = 0) {
		
		this.buffer = buffer;
		this.offset = offset;
		
		if (length != null && length != 0) {
			
			this.length = length;
			
		}
		
		this.loops = loops;
		id = 0;
		
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
				
				if (streamBuffers != null) {
					
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
				if (!buffer.stream) {
					
					al.sourcei (id, al.BUFFER, buffer.id);
					
				}
				
				#end
			
			default:
			
		}
		
	}
	
	
	public function play ():Void {
		
		#if html5
		#elseif flash
			
			if (channel != null) channel.stop ();
			var channel = buffer.src.play (pauseTime / 1000);
			
		#else
			
			if (playing || id == 0) {
				
				return;
				
			}
			
			playing = true;
			
			var time = currentTime;
			
			if (queueTimer != null) {
				
				queueTimer.stop ();
				
			}
			
			if (buffer.stream) {
				
				queueTimer = new Timer (300);
				queueTimer.run = queueTimer_onRun;
				queueTimer_onRun ();
				
			}
			
			AL.sourcePlay (id);
			
			currentTime = time;
			
			if (timer != null) {
				
				timer.stop ();
				
			}
			
			if (!buffer.stream) {
				
				timer = new Timer (length - currentTime);
				timer.run = timer_onRun;
				
			}
			
		#end
		
	}
	
	
	public function pause ():Void {
		
		#if html5
		#elseif flash
			
			if (channel != null) {
				
				pauseTime = Std.int (channel.position * 1000);
				channel.stop ();
				
			}
			
		#else
			
			playing = false;
			AL.sourcePause (id);
			
			if (timer != null) {
				
				timer.stop ();
				
			}
			
		#end
		
	}
	
	
	public function stop ():Void {
		
		#if html5
		#elseif flash
			
			pauseTime = 0;
			if (channel != null) channel.stop ();
			
		#else
			
			playing = false;
			AL.sourceStop (id);
			
			if (timer != null) {
				
				timer.stop ();
				
			}
			
		#end
		
	}
	
	
	
	
	// Event Handlers
	
	
	
	
	private function timer_onRun () {
		
		#if (cpp || neko || nodejs)
		
		playing = false;
		
		if (loops > 0) {
			
			loops--;
			currentTime = 0;
			play ();
			return;
			
		} else {
			
			AL.sourceStop (id);
			timer.stop ();
			
		}
		
		onComplete.dispatch ();
		
		#end
		
	}
	
	
	private function queueTimer_onRun () {
		
		#if (cpp || neko || nodejs)
		
		var shouldStop:Bool = false;
		if (playing) {
			
			var bufferCount:Int;
			
			if (streamBuffers == null) {
				
				bufferCount = initialBufferCount;
				streamBuffers = AL.genBuffers (bufferCount);
				
			} else {
				
				bufferCount = AL.getSourcei ( id, AL.BUFFERS_PROCESSED );
				if (bufferCount == 0) {
					
					return;
					
				}
				streamBuffers = AL.sourceUnqueueBuffers (id, bufferCount);
				
			}
			
			var data:Array<ByteArray> = lime_audio_stream_decode (buffer.handle, 65536, bufferCount);
			
			if (data == null) {
				
				shouldStop = true;
				
			} else {
				
				if (data.length != 0) {
					
					for (i in 0 ... data.length) {
						
						var ba:ByteArray = data[i];
						AL.bufferData (streamBuffers[i], format, ba, ba.length, buffer.sampleRate);
						
					}
					
					AL.sourceQueueBuffers (id, data.length, streamBuffers);
					
					var state = AL.getSourcei (id, AL.SOURCE_STATE);
					if (state != AL.PLAYING)
						AL.sourcePlay (id);
					
				} else {
					
					shouldStop = true;
					
				}
				
			}
		} else  {
			
			shouldStop = true;
			
		}
		
		if (shouldStop) {
			
			if (streamBuffers != null) {
				
				AL.deleteBuffers (streamBuffers);
				streamBuffers = null;
				
			}
			
			queueTimer.stop ();
			stop ();
			
		}
		
		#end
		
	}
	
	
	
	// Get & Set Methods
	
	
	
	
	private function get_currentTime ():Int {
		
		#if html5
			
			return 0;
			
		#elseif flash
			
			return Std.int (channel.position);
			
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
			
		#else
			
			if (buffer != null) {
				
				AL.sourceRewind (id);
				if (playing) AL.sourcePlay (id);
				AL.sourcef (id, AL.SEC_OFFSET, (value + offset) / 1000);
				
			}
			
			return value;
			
		#end
		
	}
	
	
	private function get_gain ():Float {
		
		#if html5
			
			return 1;
			
		#elseif flash
			
			return channel.soundTransform.volume;
			
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
			
		#else
			
			var samples = (buffer.data.length * 8) / (buffer.channels * buffer.bitsPerSample);
			return Std.int (samples / buffer.sampleRate * 1000) - offset;
			
		#end
		
	}
	
	
	private function set_length (value:Int):Int {
		
		return __length = value;
		
	}
	
	#if (cpp || neko || nodejs)
	private static var lime_audio_stream_decode:Dynamic = System.load ("lime", "lime_audio_stream_decode", 3);
	#end
}
