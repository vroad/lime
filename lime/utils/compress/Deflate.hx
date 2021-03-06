package lime.utils.compress;


import haxe.io.Bytes;
using lime.utils.BytesTools;


#if flash
import flash.utils.ByteArray;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


@:access(lime.utils.compress.Zlib)
class Deflate {
	
	
	public static function compress (bytes:Bytes):Bytes {
		
		#if (lime_cffi && !macro)
		
		var data = Zlib.Compress (ZlibType.DEFLATE, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.deflateRaw") (bytes.getData ());
		return Bytes.ofData (data);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.deflate ();
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function decompress (bytes:Bytes):Bytes {
		
		#if (lime_cffi && !macro)
		
		var data = Zlib.Decompress (ZlibType.DEFLATE, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.inflateRaw") (bytes.getData ());
		return Bytes.ofData (data);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.inflate ();
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
}