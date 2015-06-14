package lime;
import lime.audio.AudioBuffer;
import lime.graphics.Image;
import lime.text.Font;
import lime.utils.ByteArray;

class AssetLibrary {
	
	
	public var eventCallback:Dynamic;
	
	
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
	
	
	//public function getMusic (id:String):Dynamic /*Sound*/ {
		
	//	return getSound (id);
		
	//}
	
	
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
	
	
	private function load (handler:AssetLibrary -> Void):Void {
		
		handler (this);
		
	}
	
	
	public function loadAudioBuffer (id:String, handler:AudioBuffer -> Void):Void {
		
		handler (getAudioBuffer (id));
		
	}
	
	
	public function loadBytes (id:String, handler:ByteArray -> Void):Void {
		
		handler (getBytes (id));
		
	}
	
	
	public function loadFont (id:String, handler:Font -> Void):Void {
		
		handler (getFont (id));
		
	}
	
	
	public function loadImage (id:String, handler:Image -> Void):Void {
		
		handler (getImage (id));
		
	}
	
	
	//public function loadMusic (id:String, handler:Dynamic /*Sound*/ -> Void):Void {
		
	//	handler (getMusic (id));
		
	//}
	
	
	public function loadText (id:String, handler:String -> Void):Void {
		
		#if (tools && !display)
		
		var callback = function (bytes:ByteArray):Void {
			
			if (bytes == null) {
				
				handler (null);
				
			} else {
				
				handler (bytes.readUTFBytes (bytes.length));
				
			}
			
		}
		
		loadBytes (id, callback);
		
		#else
		
		handler (null);
		
		#end
		
	}
	
	
}