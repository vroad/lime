package lime.utils;


import haxe.io.Bytes;
import haxe.io.BytesData;


class AnonBytesUtils {
	
	
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
		#elseif cs
		return new UInt8Array (@:privateAccess new Bytes (ab.length, Reflect.field(ab, "b")));
		#else
		return new UInt8Array (@:privateAccess new Bytes (ab.length, ab.b));
		#end
		
	}
	
	
}