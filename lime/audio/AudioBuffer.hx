package lime.audio;


import haxe.io.Bytes;
import haxe.io.Path;
import lime.app.Future;
import lime.app.Promise;
import lime.audio.openal.AL;
import lime.audio.openal.ALBuffer;
import lime.utils.UInt8Array;

#if howlerjs
import lime.audio.howlerjs.Howl;
#end
#if (js && html5)
import js.html.Audio;
#elseif flash
import flash.media.Sound;
import flash.net.URLRequest;
#elseif lime_console
import lime.audio.fmod.FMODMode;
import lime.audio.fmod.FMODSound;
#end

@:access(lime.Assets)

#if !macro
@:build(lime.system.CFFI.build())
#end


class AudioBuffer {
	
	
	public var bitsPerSample:Int;
	public var channels:Int;
	public var handle:Dynamic;
	public var sourceData:Bytes;
	public var data:UInt8Array;
	public var stream(get, never):Bool;
	public var sampleRate:Int;
	public var src (get, set):Dynamic;
	
	@:noCompletion private var __srcAudio:#if (js && html5) Audio #else Dynamic #end;
	@:noCompletion private var __srcBuffer:#if lime_cffi ALBuffer #else Dynamic #end;
	@:noCompletion private var __srcCustom:Dynamic;
	@:noCompletion private var __srcFMODSound:#if lime_console FMODSound #else Dynamic #end;
	@:noCompletion private var __srcHowl:#if howlerjs Howl #else Dynamic #end;
	@:noCompletion private var __srcSound:#if flash Sound #else Dynamic #end;
	
	
	public function new () {
		
		
		
	}
	
	
	public function dispose ():Void {
		
		#if lime_console
		if (channels > 0) {
			
			src.release ();
			channels = 0;
			
		}
		#end
		
	}
	
	
	#if lime_console
	@:void
	private static function finalize (a:AudioBuffer):Void {
		
		a.dispose ();
		
	}
	#end
	
	
	public static function fromBytes (bytes:Bytes, stream:Bool = false):AudioBuffer {
		
		if (bytes == null) return null;
		
		#if lime_console
		
		lime.Lib.notImplemented ("AudioBuffer.fromBytes");
		
		#elseif (lime_cffi && !macro)
		
		var data:Dynamic = lime_audio_load (bytes, stream);
		
		if (data != null) {
			
			var audioBuffer = new AudioBuffer ();
			audioBuffer.bitsPerSample 	= data.bitsPerSample;
			audioBuffer.channels = data.channels;
			audioBuffer.data = data.data != null ? AnonBytesUtils.getUInt8ArrayFromAnonBytes (data.data) : null;
			audioBuffer.sampleRate = data.sampleRate;
			audioBuffer.length = data.length;
			audioBuffer.handle = data.handle;
			return audioBuffer;
			
		}
		
		#end
		
		return null;
		
	}
	
	
	public static function fromFile (path:String, stream:Bool = false):AudioBuffer {
		
		if (path == null) return null;
		
		#if (js && html5 && howlerjs)
		
		var audioBuffer = new AudioBuffer ();
		audioBuffer.__srcHowl = new Howl ({ src: [ path ] });
		return audioBuffer;
		
		#elseif flash
		
		switch (Path.extension (path)) {
			
			case "ogg", "wav": return null;
			default:
			
		}
		
		var audioBuffer = new AudioBuffer ();
		audioBuffer.__srcSound = new Sound (new URLRequest (path));
		return audioBuffer;
		
		#elseif lime_console
		
		var mode = StringTools.endsWith(path, ".wav") ? FMODMode.LOOP_OFF : FMODMode.LOOP_NORMAL;
		var sound:FMODSound = FMODSound.fromFile (path, mode);
		
		if (sound.valid) {
			
			// TODO(james4k): AudioBuffer needs sound info filled in
			// TODO(james4k): probably move fmod.Sound creation to AudioSource,
			// and keep AudioBuffer as raw data. not as efficient for typical
			// use, but probably less efficient to do complex copy-on-read
			// mechanisms and such. also, what do we do for compressed sounds?
			// usually don't want to decompress large music files. I suppose we
			// can specialize for those and not allow data access.
			var audioBuffer = new AudioBuffer ();
			audioBuffer.bitsPerSample = 0;
			audioBuffer.channels = 1;
			audioBuffer.data = null;
			audioBuffer.sampleRate = 0;
			audioBuffer.__srcFMODSound = sound;
			cpp.vm.Gc.setFinalizer (audioBuffer, cpp.Function.fromStaticFunction (finalize));
			return audioBuffer;
			
		}
		
		#elseif (lime_cffi && !macro)
		
		var data:Dynamic = lime_audio_load (path, stream);
		
		if (data != null) {
			
			var audioBuffer = new AudioBuffer ();
			audioBuffer.bitsPerSample = data.bitsPerSample;
			audioBuffer.channels = data.channels;
			audioBuffer.data = data.data != null ? AnonBytesUtils.getUInt8ArrayFromAnonBytes (data.data) : null;
			audioBuffer.sampleRate = data.sampleRate;
			audioBuffer.length = data.length;
			audioBuffer.handle = data.handle;
			return audioBuffer;
			
		}
		
		#end
		
		return null;
		
	}
	
	
	public static function fromFiles (paths:Array<String>):AudioBuffer {
		
		#if (js && html5 && howlerjs)
		
		var audioBuffer = new AudioBuffer ();
		audioBuffer.__srcHowl = new Howl ({ src: paths });
		return audioBuffer;
		
		#else
		
		var buffer = null;
		
		for (path in paths) {
			
			buffer = AudioBuffer.fromFile (path);
			if (buffer != null) break;
			
		}
		
		return buffer;
		
		#end
		
	}
	
	
		
		#if (js && html5 && howlerjs)
		
		var audioBuffer = new AudioBuffer ();
		audioBuffer.__srcHowl = new Howl ({ src: [ url ] });
		audioBuffer.__srcHowl.on ("load", function () { handler (audioBuffer); });
		audioBuffer.__srcHowl.on ("loaderror", function () { handler (null); });
		audioBuffer.__srcHowl.load ();
		
		#else
		
		if (url != null && url.indexOf ("http://") == -1 && url.indexOf ("https://") == -1) {
			
			handler (AudioBuffer.fromFile (url, stream));
			
		} else {
			
			// TODO: Support streaming sound
			
			#if flash
			
			var loader = new flash.net.URLLoader ();
			loader.addEventListener (flash.events.Event.COMPLETE, function (_) {
				handler (AudioBuffer.fromBytes (cast loader.data));
			});
			loader.addEventListener (flash.events.IOErrorEvent.IO_ERROR, function (_) {
				handler (null);
			});
			loader.load (new flash.net.URLRequest (url));
			
			#else
			
			//var loader = new URLLoader ();
			//loader.onComplete.add (function (_) {
				//var bytes = Bytes.ofString (loader.data);
				//handler (AudioBuffer.fromBytes (bytes));
			//});
			//loader.onIOError.add (function (_, msg) {
				//handler (null);
			//});
			//loader.load (new URLRequest (url));
			
			#end
			
		}
		
		#end
		
	}
	
	
	public static function loadFromFile (path:String):Future<AudioBuffer> {
		
		var promise = new Promise<AudioBuffer> ();
		
		var audioBuffer = AudioBuffer.fromFile (path);
		
		if (audioBuffer != null) {
			
			#if flash
			
			audioBuffer.__srcSound.addEventListener (flash.events.Event.COMPLETE, function (event) {
				
				promise.complete (audioBuffer);
				
			});
			
			audioBuffer.__srcSound.addEventListener (flash.events.ProgressEvent.PROGRESS, function (event) {
				
				if (event.bytesTotal == 0) {
					
					promise.progress (0);
					
				} else {
					
					promise.progress (event.bytesLoaded / event.bytesTotal);
					
				}
				
			});
			
			audioBuffer.__srcSound.addEventListener (flash.events.IOErrorEvent.IO_ERROR, promise.error);
			
			#elseif (js && html5 && howlerjs)
			
			if (audioBuffer != null) {
				
				audioBuffer.__srcHowl.on ("load", function () { 
					
					promise.complete (audioBuffer);
					
				});
				
				audioBuffer.__srcHowl.on ("loaderror", function () {
					
					promise.error (null);
					
				});
				
				audioBuffer.__srcHowl.load ();
				
			}
			
			#else
			
			promise.complete (audioBuffer);
			
			#end
			
		} else {
			
			promise.error (null);
			
		}
		
		return promise.future;
		
	}
	
	
	public static function loadFromFiles (paths:Array<String>):Future<AudioBuffer> {
		
		var promise = new Promise<AudioBuffer> ();
		
		#if (js && html5 && howlerjs)
		
		var audioBuffer = AudioBuffer.fromFiles (paths);
		
		if (audioBuffer != null) {
			
			audioBuffer.__srcHowl.on ("load", function () { 
				
				promise.complete (audioBuffer);
				
			});
			
			audioBuffer.__srcHowl.on ("loaderror", function () {
				
				promise.error (null);
				
			});
			
			audioBuffer.__srcHowl.load ();
			
		} else {
			
			promise.error (null);
			
		}
		
		#else
		
		promise.completeWith (new Future<AudioBuffer> (function () return fromFiles (paths)));
		
		#end
		
		return promise.future;
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	private function get_src ():Dynamic {
		
		#if (js && html5)
		#if howlerjs
		
		return __srcHowl;
		
		#else
		
		return __srcAudio;
		
		#end
		#elseif flash
		
		return __srcSound;
		
		#elseif lime_console
		
		return __srcFMODSound;
		
		#else
		
		return __srcCustom;
		
		#end
		
	}
	
	
	private function set_src (value:Dynamic):Dynamic {
		
		#if (js && html5)
		#if howlerjs
		
		return __srcHowl = value;
		
		#else
		
		return __srcAudio = value;
		
		#end
		#elseif flash
		
		return __srcSound = value;
		
		#elseif lime_console
		
		return __srcFMODSound = value;
		
		#else
		
		return __srcCustom = value;
		
		#end
		
	}
	
	
	private function get_stream ():Bool {
		
		return handle != null;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cffi && !macro)
	@:cffi private static function lime_audio_load (data:Dynamic, stream:Bool):Dynamic;
	#end
	
	
}