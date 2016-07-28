package lime.utils.compress;


import haxe.io.Bytes;
import lime._internal.utils.LimeBytes;
import lime.utils.AnonBytes;
using lime.utils.BytesTools;


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
		
		var data = Compress (bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
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
		
		var data = Decompress (bytes);
		if (data == null) return null;
		return Bytes.ofAnonBytes (data);
		
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
	@:cffi private static function Compress (data:LimeBytes):AnonBytes { throw null; }
	@:cffi private static function Decompress (data:LimeBytes):AnonBytes { throw null; }
	#end
	
	
}