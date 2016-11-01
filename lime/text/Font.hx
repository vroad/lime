package lime.text;


import haxe.io.Bytes;
import lime._internal.text.FontHandle;
import lime._internal.utils.CString;
import lime._internal.utils.LimeBytes;
import lime._internal.utils.StdWString;
import lime.graphics.Image;
import lime.graphics.ImageBuffer;
import lime.math.Vector2;
import lime.system.CFFIPointer;
import lime.system.System;
import lime.utils.UInt8Array;

#if (js && html5)
import js.html.CanvasElement;
import js.html.CanvasRenderingContext2D;
#end

#if (lime_cffi && !macro)
import haxe.io.Path;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end

#if (!display && !nodejs && !macro)
@:autoBuild(lime.Assets.embedFont())
#end

@:access(lime.text.Glyph)


@:cffiInterface("Font.xml")
@:cffiCppType("lime::Font")
class Font {
	
	
	public var ascender (get, null):Int;
	public var descender (get, null):Int;
	public var height (get, null):Int;
	public var name (default, null):String;
	public var numGlyphs (get, null):Int;
	@:cffiHandle public var src (default, null):Dynamic;
	public var underlinePosition (get, null):Int;
	public var underlineThickness (get, null):Int;
	public var unitsPerEM (get, null):Int;
	
	@:noCompletion private var __fontPath:String;
	#if lime_cffi
	@:noCompletion private var __fontPathWithoutDirectory:String;
	#end
	
	
	public function new (name:String = null) {
		
		if (name != null) {
			
			this.name = name;
			
		}
		
		if (__fontPath != null) {
			
			__fromFile (__fontPath);
			
		}
		
	}
	
	
	public function decompose ():NativeFontData {
		
		#if (lime_cffi && !macro)
		
		if (src == null) throw "Uninitialized font handle.";
		var data:Dynamic = Decompose (1024 * 20);
		return data;
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function fromBytes (bytes:Bytes):Font {
		
		if (bytes == null) return null;
		
		var font = new Font ();
		font.__fromBytes (bytes);
		
		#if (lime_cffi && !macro)
		return (font.src != null) ? font : null;
		#else
		return font;
		#end
		
	}
	
	
	public static function fromFile (path:String):Font {
		
		if (path == null) return null;
		
		var font = new Font ();
		font.__fromFile (path);
		
		#if (lime_cffi && !macro)
		return (font.src != null) ? font : null;
		#else
		return font;
		#end
		
	}
	
	
	public function getGlyph (character:String):Glyph {
		
		#if (lime_cffi && !macro)
		return GetGlyphIndex (character);
		#else
		return -1;
		#end
		
	}
	
	
	public function getGlyphs (characters:String = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^`'\"/\\&*()[]{}<>|:;_-+=?,. "):Array<Glyph> {
		
		#if (lime_cffi && !macro)
		var glyphs:Dynamic = GetGlyphIndices (characters);
		return glyphs;
		#else
		return null;
		#end
		
	}
	
	
	public function getGlyphMetrics (glyph:Glyph):GlyphMetrics {
		
		#if (lime_cffi && !macro)
		var value:Dynamic = GetGlyphMetrics (glyph);
		var metrics = new GlyphMetrics ();
		
		metrics.advance = new Vector2 (value.horizontalAdvance, value.verticalAdvance);
		metrics.height = value.height;
		metrics.horizontalBearing = new Vector2 (value.horizontalBearingX, value.horizontalBearingY);
		metrics.verticalBearing = new Vector2 (value.verticalBearingX, value.verticalBearingY);
		
		return metrics;
		#else
		return null;
		#end
		
	}
	
	
	public function renderGlyph (glyph:Glyph, fontSize:Int):Image {
		
		#if 0
		
		__setSize (fontSize);
		
		var bytes = Bytes.alloc (0);
		//bytes.endian = (System.endianness == BIG_ENDIAN ? "bigEndian" : "littleEndian");
		
		var dataPosition = 0;
		var data:Dynamic = RenderGlyph (src, glyph, bytes);
		
		if (data != null) {
			
			var width = bytes.readUnsignedInt ();
			var height = bytes.readUnsignedInt ();
			var x = bytes.readInt ();
			var y = bytes.readInt ();
			
			var buffer = new ImageBuffer (BytesUtil.getUInt8ArrayFromAnonBytes (data), width, height, 1);
			var image = new Image (buffer, 0, 0, width, height);
			image.x = x;
			image.y = y;
			
			return image;
			
		}
		
		#end
		
		return null;
		
	}

	
	public function renderGlyphs (glyphList:Array<Glyph>, fontSize:Int):Array<Image> {
		
		#if 0
		
		lime_font_set_size (src, fontSize);
		
		var bytes = new ByteArray (glyphList.length * 16);
		bytes.endian = (System.endianness == BIG_ENDIAN ? "bigEndian" : "littleEndian");
		
		var rawImages:Array<Dynamic> = RenderGlyphs (src, glyphList, bytes);
		
		if (rawImages != null) {
			
			var results:Array<Image> = [];
			for (i in 0 ... rawImages.length)
			{
				var width = bytes.readUnsignedInt ();
				var height = bytes.readUnsignedInt ();
				var x = bytes.readInt ();
				var y = bytes.readInt ();
				
				var rawImage:AnonBytes = rawImages[i];
				var buffer, image = null;
				if (rawImage != null)
				{
					
					buffer = new ImageBuffer (BytesUtil.getUInt8ArrayFromAnonBytes (rawImage), width, height, 1);
					image = new Image (buffer, 0, 0, width, height);
					image.x = x;
					image.y = y;
					
				}
				results.push (image);
			}
			
			return results;
			
		}
		
		#end
		
		return null;
		
	}
		
	@:noCompletion private function __fromBytes (bytes:Bytes):Void {
		
		__fontPath = null;
		
		#if (lime_cffi && !macro)
		
		__fontPathWithoutDirectory = null;
		
		src = Load (bytes);
		
		if (src != null && name == null) {
			
			name = GetFamilyName ();
			
		}
		
		#end
		
	}
	
	
	@:noCompletion private function __fromFile (path:String):Void {
		
		__fontPath = path;
		
		#if (lime_cffi && !macro)
		
		__fontPathWithoutDirectory = Path.withoutDirectory (__fontPath);
		
		src = Load (__fontPath);
		
		if (src != null && name == null) {
			
			name = GetFamilyName ();
			
		}
		
		#end
		
	}
	
	
	@:noCompletion private function __setSize (size:Int):Void {
		
		#if (lime_cffi && !macro)
		SetSize (size);
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	private function get_ascender ():Int {
		
		#if (lime_cffi && !macro)
		return GetAscender ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_descender ():Int {
		
		#if (lime_cffi && !macro)
		return GetDescender ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_height ():Int {
		
		#if (lime_cffi && !macro)
		return GetHeight ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_numGlyphs ():Int {
		
		#if (lime_cffi && !macro)
		return GetNumGlyphs ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_underlinePosition ():Int {
		
		#if (lime_cffi && !macro)
		return GetUnderlinePosition ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_underlineThickness ():Int {
		
		#if (lime_cffi && !macro)
		return GetUnderlineThickness ();
		#else
		return 0;
		#end
		
	}
	
	
	private function get_unitsPerEM ():Int {
		
		#if (lime_cffi && !macro)
		return GetUnitsPerEM ();
		#else
		return 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cffi && !macro)
	@:cffi private function GetAscender ():Int;
	@:cffi private function GetDescender ():Int;
	@:cffi private function GetFamilyName ():StdWString;
	@:cffi private function GetGlyphIndex (character:CString):Int;
	@:cffi private function GetGlyphIndices (characters:CString):Dynamic;
	@:cffi private function GetGlyphMetrics (index:Int):Dynamic;
	@:cffi private function GetHeight ():Int;
	@:cffi private function GetNumGlyphs ():Int;
	@:cffi private function GetUnderlinePosition ():Int;
	@:cffi private function GetUnderlineThickness ():Int;
	@:cffi private function GetUnitsPerEM ():Int;
	@:cffi private static function Load (data:Dynamic):FontHandle;
	@:cffi private function Decompose (size:Int):Dynamic;
	@:cffi private function RenderGlyph (index:Int, data:LimeBytes):Dynamic;
	@:cffi private function RenderGlyphs (indices:Dynamic, data:LimeBytes):Array<Dynamic>;
	@:cffi private function SetSize (size:Int):Void;
	#end
	
	
}


typedef NativeFontData = {
	
	var has_kerning:Bool;
	var is_fixed_width:Bool;
	var has_glyph_names:Bool;
	var is_italic:Bool;
	var is_bold:Bool;
	var num_glyphs:Int;
	var family_name:String;
	var style_name:String;
	var em_size:Int;
	var ascend:Int;
	var descend:Int;
	var height:Int;
	var glyphs:Array<NativeGlyphData>;
	var kerning:Array<NativeKerningData>;
	
}


typedef NativeGlyphData = {
	
	var char_code:Int;
	var advance:Int;
	var min_x:Int;
	var max_x:Int;
	var min_y:Int;
	var max_y:Int;
	var points:Array<Int>;
	
}


typedef NativeKerningData = {
	
	var left_glyph:Int;
	var right_glyph:Int;
	var x:Int;
	var y:Int;
	
}
