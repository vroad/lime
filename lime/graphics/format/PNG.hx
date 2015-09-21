package lime.graphics.format;


import haxe.io.Bytes;
import lime.graphics.Image;
import lime.system.CFFI;
import lime.utils.ByteArray;

#if format
import format.png.Data;
import format.png.Writer;
import format.tools.Deflate;
import haxe.io.Bytes;
import haxe.io.BytesOutput;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


class PNG {
	
	
	public static function decodeBytes (bytes:ByteArray, decodeData:Bool = true):Image {
		
		#if ((cpp || neko || nodejs) && !macro)
		
		var bufferData:Dynamic = lime_png_decode_bytes (bytes, decodeData);
		
		if (bufferData != null) {
			
			var buffer = new ImageBuffer (bufferData.data, bufferData.width, bufferData.height, bufferData.bpp, bufferData.format);
			buffer.transparent = bufferData.transparent;
			return new Image (buffer);
			
		}
		
		#end
		
		return null;
		
	}
	
	
	public static function decodeFile (path:String, decodeData:Bool = true):Image {
		
		#if ((cpp || neko || nodejs) && !macro)
		
		var bufferData:Dynamic = lime_png_decode_file (path, decodeData);
		
		if (bufferData != null) {
			
			var buffer = new ImageBuffer (bufferData.data, bufferData.width, bufferData.height, bufferData.bpp, bufferData.format);
			buffer.transparent = bufferData.transparent;
			return new Image (buffer);
			
		}
		
		#end
		
		return null;
		
	}
	
	
	public static function encode (image:Image):ByteArray {
		
		if (image.premultiplied || image.format != RGBA32) {
			
			// TODO: Handle encode from different formats
			
			image = image.clone ();
			image.premultiplied = false;
			image.format = RGBA32;
			
		}
		
		#if java
		
		#elseif (sys && (!disable_cffi || !format) && !macro)
		
		if (CFFI.enabled) {
			
			var data:Dynamic = lime_image_encode (image.buffer, 0, 0);
			var bytes = @:privateAccess new Bytes (data.length, data.b);
			return ByteArray.fromBytes (bytes);
			
		}
		
		#if (!html5 && format)
		
		else {
			
			try {
				
				var bytes = Bytes.alloc (image.width * image.height * 4 + image.height);
				
				#if flash
				var sourceBytes = Bytes.ofData (image.buffer.data.getByteBuffer ());
				#else
				var sourceBytes = cast image.buffer.data;
				#end
				
				var sourceIndex:Int, index:Int;
				
				for (y in 0...image.height) {
					
					sourceIndex = y * image.width * 4;
					index = y * image.width * 4 + y;
					
					bytes.set (index, 0);
					bytes.blit (index + 1, sourceBytes, sourceIndex, image.width * 4);
					
				}
				
				var data = new List ();
				data.add (CHeader ({ width: image.width, height: image.height, colbits: 8, color: ColTrue (true), interlaced: false }));
				data.add (CData (Deflate.run (bytes)));
				data.add (CEnd);
				
				var output = new BytesOutput ();
				var png = new Writer (output);
				png.write (data);
				
				#if flash
				return output.getBytes ().getData ();
				#else
				return ByteArray.fromBytes (output.getBytes ());
				#end
				
			} catch (e:Dynamic) { }
			
		}
		
		#end
		#end
		
		return null;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if ((cpp || neko || nodejs) && !macro)
	@:cffi private static function lime_png_decode_bytes (data:Dynamic, decodeData:Bool):Dynamic;
	@:cffi private static function lime_png_decode_file (path:String, decodeData:Bool):Dynamic;
	@:cffi private static function lime_image_encode (data:Dynamic, type:Int, quality:Int):Dynamic;
	#end
	
	
}