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
	
}