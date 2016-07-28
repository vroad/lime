package lime.utils.compress;


import haxe.io.Bytes;
using lime.utils.BytesTools;


@:access(lime.utils.compress.Zlib)
class GZip {
	
	
	public static function compress (bytes:Bytes):Bytes {
		
		#if (lime_native && !macro)
		
		var data = Zlib.Compress (ZlibType.GZIP, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.gzip") (bytes.getData ());
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function decompress (bytes:Bytes):Bytes {
		
		#if (lime_native && !macro)
		
		var data:Dynamic = Zlib.Decompress (ZlibType.GZIP, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.ungzip") (bytes.getData ());
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
}