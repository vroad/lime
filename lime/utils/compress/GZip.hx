package lime.utils.compress;


import haxe.io.Bytes;


@:access(lime.utils.compress.Zlib)
class GZip {
	
	
	public static function compress (bytes:Bytes):Bytes {
		
		#if (lime_native && !macro)
		
		var data:Dynamic = Zlib.Compress (ZlibType.GZIP, bytes);
		if (data == null) return null;
		return @:privateAccess new Bytes (data.length, data.b);
		
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
		return @:privateAccess new Bytes (data.length, data.b);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.ungzip") (bytes.getData ());
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
}