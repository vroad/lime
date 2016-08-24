package lime.utils.compress;


import haxe.io.Bytes;
import lime._internal.utils.LimeBytes;
using lime.utils.BytesTools;

#if flash
import flash.utils.ByteArray;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("Zlib.xml")
@:cffiCppType("lime::Zlib")
class Zlib {
	
	
	public static function compress (bytes:Bytes):Bytes {
		
		#if (lime_cffi && !macro)
		
		var data = Compress (ZlibType.ZLIB, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.deflate") (bytes.getData ());
		return Bytes.ofData (data);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.compress ();
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function decompress (bytes:Bytes):Bytes {
		
		#if (lime_cffi && !macro)
		
		var data = Decompress (ZlibType.ZLIB, bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
		#elseif (js && html5)
		
		var data = untyped __js__ ("pako.inflate") (bytes.getData ());
		return Bytes.ofData (data);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.uncompress ();
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if lime_cffi
	@:noCompletion @:cffi private static function Compress (type:ZlibType, data:LimeBytes):Dynamic { throw null; }
	@:noCompletion @:cffi private static function Decompress (type:ZlibType, data:LimeBytes):Dynamic { throw null; }
	#end
	
	
}