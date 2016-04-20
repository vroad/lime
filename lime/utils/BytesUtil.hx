package lime.utils;

import haxe.io.Bytes;

class BytesUtil
{
	
	public static function getAnonBytesFromTypedArray (array:ArrayBufferView):AnonBytes {
		
		#if js
		return {length:array.byteLength, b:array};
		#else
		return cast array.buffer;
		#end
		
	}
	
	public static function getUInt8ArrayFromAnonBytes (ab:AnonBytes):UInt8Array {
		
		#if js
		return ab.b;
		#else
		return new UInt8Array (@:privateAccess new Bytes (ab.length, ab.b));
		#end
		
	}
	
	public static function createBytes (length:Int, b:Dynamic):Bytes {
		
		#if ((js && haxe < 3.2) || !js)
		@:privateAccess return new Bytes (length, b);
		#else
		@:privateAccess return new Bytes (b);
		#end
		
	}
	
}