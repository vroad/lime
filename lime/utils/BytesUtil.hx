package lime.utils;

import haxe.io.Bytes;

class BytesUtil
{

	public static function getBytesFromByteArray(byteArray:ByteArray) {
		
		#if nodejs
		@:privateAccess return new Bytes (byteArray.length, cast byteArray.byteView);
		#elseif js
		@:privateAccess return new Bytes (byteArray.byteView.buffer);
		#else
		return byteArray;
		#end
		
	}

	public static function getBytesFromUInt8Array(u8a:UInt8Array) {
		
		#if nodejs
		@:privateAccess return new Bytes (u8a.byteLength, cast u8a.buffer);
		#elseif js
		@:privateAccess return new Bytes (u8a.buffer);
		#else
		return u8a.buffer;
		#end
		
	}

	public static function getUInt8ArrayFromByteArray(byteArray:ByteArray) {
		
		#if js
		return byteArray.byteView;
		#elseif flash
		var u8a:UInt8Array = new UInt8Array (byteArray.length);
		u8a.buffer.getData ().readBytes (byteArray);
		return u8a;
		#else
		return new UInt8Array (byteArray);
		#end
		
	}
	
	public static function getUInt8ArrayFromAnonStructure (as:{b:Dynamic, length:Int}) {
		
		#if js
		return as.b;
		#else
		return new UInt8Array (@:privateAccess new Bytes (as.length, as.b));
		#end
		
	}
}