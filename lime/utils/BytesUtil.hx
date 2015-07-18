package lime.utils;

import haxe.io.Bytes;

class BytesUtil
{

	public static function getBytesFromByteArray(byteArray:ByteArray) {
		
		#if nodejs
		@:privateAccess return new Bytes (byteArray.length, cast byteArray.byteView);
		#else
		return byteArray;
		#end
		
	}

	public static function getBytesFromUInt8Array(u8a:UInt8Array) {
		
		#if nodejs
		@:privateAccess return new Bytes (u8a.byteLength, cast u8a);
		#else
		return u8a.buffer;
		#end
		
	}

	public static function getUInt8ArrayFromByteArray(byteArray:ByteArray) {
		
		#if nodejs
		return byteArray.byteView;
		#else
		return new UInt8Array (byteArray);
		#end
		
	}
	
}