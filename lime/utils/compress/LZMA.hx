package lime.utils.compress;


import haxe.io.Bytes;
import lime._internal.utils.LimeBytes;


#if flash
import flash.utils.CompressionAlgorithm;
import flash.utils.ByteArray;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("LZMA.xml")
@:cffiCppType("lime::LZMA")
class LZMA {
	
	
	public static function compress (bytes:Bytes):Bytes {
		
		#if (lime_native && !macro)
		
		var data:Dynamic = Compress (bytes);
		if (data == null) return null;
		return @:privateAccess new Bytes (data.length, data.b);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.compress (CompressionAlgorithm.LZMA);
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function decompress (bytes:Bytes):Bytes {
		
		#if (lime_native && !macro)
		
		var data:Dynamic = Decompress (bytes);
		if (data == null) return null;
		return @:privateAccess new Bytes (data.length, data.b);
		
		#elseif flash
		
		var byteArray:ByteArray = cast bytes.getData ();
		
		var data = new ByteArray ();
		data.writeBytes (byteArray);
		data.uncompress (CompressionAlgorithm.LZMA);
		
		return Bytes.ofData (data);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if lime_native
	@:cffi private static function Compress (data:LimeBytes):Dynamic { throw null; }
	@:cffi private static function Decompress (data:LimeBytes):Dynamic { throw null; }
	#end
	
	
}