package lime;

import lime.app.Event;
import lime.app.Future;
import lime.audio.AudioBuffer;
import lime.graphics.Image;
import lime.text.Font;
import lime.utils.ByteArray;

class AssetLibrary {
	
	
	public var onChange = new Event<Void->Void> ();
	
	
	public function new () {
		
		
		
	}
	
	
	public function exists (id:String, type:String):Bool {
		
		return false;
		
	}
	
	
	public function getAudioBuffer (id:String):AudioBuffer {
		
		return null;
		
	}
	
	
	public function getBytes (id:String):ByteArray {
		
		return null;
		
	}
	
	
	public function getFont (id:String):Font {
		
		return null;
		
	}
	
	
	public function getImage (id:String):Image {
		
		return null;
		
	}
	
	
	public function getPath (id:String):String {
		
		return null;
		
	}
	
	
	public function getText (id:String):String {
		
		#if (tools && !display)
		
		var bytes = getBytes (id);
		
		if (bytes == null) {
			
			return null;
			
		} else {
			
			return bytes.readUTFBytes (bytes.length);
			
		}
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public function isLocal (id:String, type:String):Bool {
		
		return true;
		
	}
	
	
	public function list (type:String):Array<String> {
		
		return null;
		
	}
	
	
	private function load ():Future<AssetLibrary> {
		
		return new Future<AssetLibrary> (function () return this);
		
	}
	
	
	public function loadAudioBuffer (id:String):Future<AudioBuffer> {
		
		return new Future<AudioBuffer> (function () return getAudioBuffer (id));
		
	}
	
	
	public function loadBytes (id:String):Future<ByteArray> {
		
		return new Future<ByteArray> (function () return getBytes (id));
		
	}
	
	
	public function loadFont (id:String):Future<Font> {
		
		return new Future<Font> (function () return getFont (id));
		
	}
	
	
	public function loadImage (id:String):Future<Image> {
		
		return new Future<Image> (function () return getImage (id));
		
	}
	
	
	public function loadText (id:String):Future<String> {
		
		return loadBytes (id).then (function (bytes) {
			
			return new Future<String> (function () {
				
				if (bytes == null) {
					
					return null;
					
				} else {
					
					return bytes.readUTFBytes (bytes.length);
					
				}
				
			});
			
		});
		
	}
	
	
	public function unload ():Void {
		
		
		
	}
	
	
}
