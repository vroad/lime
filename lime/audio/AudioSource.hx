package lime.audio;


import lime.app.Event;
import lime.audio.openal.AL;
import lime.audio.openal.ALSource;
import lime.math.Vector4;
import lime.system.System;
import lime.utils.AnonBytesUtils;
import lime.utils.UInt8Array;

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
	public var position (get, set):Vector4;
	
	@:noCompletion private var backend:AudioSourceBackend;
	
	
	public function new (buffer:AudioBuffer = null, offset:Int = 0, length:Null<Int> = null, loops:Int = 0) {
		
		this.buffer = buffer;
		this.offset = offset;
		
		backend = new AudioSourceBackend (this);
		
		if (length != null && length != 0) {
			
			this.length = length;
			
		}
		
		this.loops = loops;
		playing = false;
        #if lime_cffi
		bufferTime = 1000;
		finishedDecoding = false;
        #end
		
		if (buffer != null) {
			
			init ();
			
		}
		
	}
	
	
	public function dispose ():Void {
		
		backend.dispose ();
		
	}
	
	
	private function init ():Void {
		
		backend.init ();
		
	}
	
	
	public function play ():Void {
		
		backend.play ();
		
	}
	
	
	public function pause ():Void {
		
		backend.pause ();
		
	}
	
	
	public function stop ():Void {
		
		backend.stop ();
		
	}
	
	
	private function streamTimer_onRun () {
		
		#if lime_cffi
		
		var sourceState:Int = AL.getSourcei (id, AL.SOURCE_STATE);
		if (playing && !finishedDecoding) {
			
			var bufferCount:Int;
			var buffers:Array<Int>;
			
			if (streamBuffers == null) {
				
				bufferCount = length < minimumBufferTime ? 1 : initialBufferCount;
				buffers = streamBuffers = AL.genBuffers (bufferCount);
				trace(buffers[0]);
				
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
				
				var numSamples:Int = lime_audio_stream_decode (buffer.handle, AnonBytesUtils.getAnonBytesFromTypedArray (audioSamples), bufferSize, writeOffset);
				
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
		
		return backend.getCurrentTime ();
		
	}
	
	
	private function set_currentTime (value:Int):Int {
		
		return backend.setCurrentTime (value);
		
	}
	
	
	private function get_gain ():Float {
		
		return backend.getGain ();
		
	}
	
	
	private function set_gain (value:Float):Float {
		
		return backend.setGain (value);
		
	}
	
	
	private function get_length ():Int {
		
		return backend.getLength ();
		
	}
	
	
	private function set_length (value:Int):Int {
		
		return backend.setLength (value);
		
	}
	
	
	private function get_loops ():Int {
		
		return backend.getLoops ();
		
	}
	
	
	private function set_loops (value:Int):Int {
		
		return backend.setLoops (value);
		
	}
	
	private function getBufferSize ():Int {
		
        #if lime_cffi
		return Std.int (buffer.sampleRate * buffer.bitsPerSample / 8 * buffer.channels * Math.max (bufferTime, minimumBufferTime) / 1000 / streamBuffers.length);
        #else
        return 0;
        #end
		
	}
	
	private function getMinimalBufferCountForLoop ():Int {
		
        #if lime_cffi
		return Std.int (Math.max (Math.floor (minimumBufferTime / length), 2));
        #else
        return 0;
        #end
		
	}
	
	private function get_position ():Vector4 {
		
		return backend.getPosition ();
		
	}
	
	
	private function set_position (value:Vector4):Vector4 {
		
		return backend.setPosition (value);
		
	}
	
	
	#if lime_cffi
	@:cffi private static function lime_audio_stream_decode (handle:Dynamic, data:Dynamic, readSize:Int, writeOffset:Int):Int;
	@:cffi private static function lime_audio_stream_seek (data:Dynamic, seconds:Float):Bool;
	#end
}


#if flash
@:noCompletion private typedef AudioSourceBackend = lime._backend.flash.FlashAudioSource;
#elseif (js && html5)
@:noCompletion private typedef AudioSourceBackend = lime._backend.html5.HTML5AudioSource;
#else
@:noCompletion private typedef AudioSourceBackend = lime._backend.native.NativeAudioSource;
#end