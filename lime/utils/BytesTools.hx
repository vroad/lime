package lime.utils;
import haxe.io.Bytes;
import haxe.io.BytesData;

class BytesTools {
	
	
	public static function ofAnonBytes (clazz:Class<haxe.io.Bytes>, ab:AnonBytes):haxe.io.Bytes {
		
		#if js
		return haxe.io.Bytes.ofData ((ab.b : UInt8Array).buffer);
		#else
		return haxe.io.Bytes.ofData (ab.b);
		#end
		
	}
	
	
	public static function ofLengthAndData (clazz:Class<haxe.io.Bytes>, length:Int, b:BytesData):haxe.io.Bytes {
		
		#if ((js && haxe < 3.2) || !js)
		@:privateAccess return new haxe.io.Bytes (length, b);
		#else
		@:privateAccess return new haxe.io.Bytes (b);
		#end
		
	}
	
	
}