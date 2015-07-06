package lime.audio;


import haxe.io.Bytes;
import lime.audio.openal.AL;
import lime.system.System;
import lime.utils.ByteArray;
import lime.utils.Float32Array;

#if (js && html5)
import js.html.Audio;
#elseif flash
import flash.media.Sound;
#end


class AudioBuffer {
	
	
	public var bitsPerSample:Int;
	public var channels:Int;
	public var handle:Dynamic;
	public var sourceData:ByteArray;
	public var data:ByteArray;
	public var id:UInt;
	public var stream(get, never):Bool;
	public var sampleRate:Int;
	
	#if (js && html5)
	public var src:Audio;
	#elseif flash
	public var src:Sound;
	#else
	public var src:Dynamic;
	#end
	
	
	public function new () {
		
		id = 0;
		
	}
	
	
	@:noCompletion private function get_stream():Bool {
		
		return handle != null || sourceData != null;
		
	}
	
	
	public static function fromBytes (bytes:ByteArray, stream:Bool = false):AudioBuffer {
		
		#if (cpp || neko || nodejs)
			
			var data = lime_audio_load (bytes, stream);
			
			if (data != null) {
				
				var audioBuffer = new AudioBuffer ();
				audioBuffer.bitsPerSample = data.bitsPerSample;
				audioBuffer.channels = data.channels;
				audioBuffer.handle = data.handle;
				audioBuffer.sourceData = data.sourceData;
				#if nodejs
				audioBuffer.data = ByteArray.fromBytes(@:privateAccess new Bytes(data.data.length, data.data.b.buffer));
				#else
				audioBuffer.data = ByteArray.fromBytes (@:privateAccess new Bytes (data.data.length, data.data.b));
				#end
				audioBuffer.sampleRate = data.sampleRate;
				return audioBuffer;
				
			}
			
		#end
		
		return null;
		
	}
	
	
	public static function fromFile (path:String, stream:Bool = false):AudioBuffer {
		
		#if (cpp || neko || nodejs)
			
			var data = lime_audio_load (path, stream);
			
			if (data != null) {
				
				var audioBuffer = new AudioBuffer ();
				audioBuffer.bitsPerSample = data.bitsPerSample;
				audioBuffer.channels = data.channels;
				audioBuffer.handle = data.handle;
				audioBuffer.sourceData = data.sourceData;
				#if nodejs
				audioBuffer.data = ByteArray.fromBytes(@:privateAccess new Bytes(data.data.length, data.data.b.buffer));
				#else
				audioBuffer.data = ByteArray.fromBytes (@:privateAccess new Bytes (data.data.length, data.data.b));
				#end
				audioBuffer.sampleRate = data.sampleRate;
				return audioBuffer;
				
			}
			
		#end
		
		return null;
		
	}
	
	
	public static function fromURL (url:String, handler:AudioBuffer->Void):Void {
		
		// TODO
		
	}
	
	
	#if (cpp || neko || nodejs)
	private static var lime_audio_load:Dynamic = System.load ("lime", "lime_audio_load", 2);
	#end
	
	
}