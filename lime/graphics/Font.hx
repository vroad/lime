package lime.graphics;


import haxe.io.Bytes;
import lime.graphics.Image;
import lime.utils.ByteArray;
import lime.utils.UInt8Array;
import lime.system.System;

#if (js && html5)
import js.html.CanvasElement;
import js.html.CanvasRenderingContext2D;
#end

#if 0
@:autoBuild(lime.Assets.embedFont())
#end

class Font {


	public var fontName (default, null):String;
	
	@:noCompletion private var __fontPath:String;
	@:noCompletion private var __handle:Dynamic;
	public var glyphs:Map<Int, Map<Int, GlyphRect>>;
	private var fontData:NativeFontData;
	
	private static var fontNames:Map<String, Font> = new Map();
	
	private function new (fontName:String = null) {

		this.fontName = fontName;
		this.glyphs = new Map<Int, Map<Int, GlyphRect>>();

	}
	
	
	public function createImage (size:Int, text:String):Array<GlyphRect> {
		
		#if (js && html5)

		/*
		if (__canvas == null) {

			__canvas = cast js.Browser.document.createElement ("canvas");
			__context = cast __canvas.getContext ("2d");

		}

		__canvas.width = __canvas.height = 128;
		__context.fillStyle = "#000000";
		__context.textBaseline = "top";
		__context.textAlign = "left";
		__context.font = size + "px " + fontFace;

		// canvas doesn't give the appropriate metrics so the values have to be padded...
		var padding = size / 4;

		var x = 0.0, y = 0.0, i = 0;

		var height = size + padding;

		while (i < glyphs.length) {

			var c = glyphs.charAt(i++);
			var metrics = __context.measureText (c);
			var width = metrics.width + 4; // fudge because of incorrect text metrics

			if (x + width > __canvas.width) {

				y += height + 1;
				x = 0;

			}

			if (y + height > __canvas.height) {

				if (__canvas.width < __canvas.height) {

					__canvas.width *= 2;

				} else {

					__canvas.height *= 2;

				}

				__context.clearRect (0, 0, __canvas.width, __canvas.height);
				__context.textBaseline = "top";
				__context.textAlign = "left";
				__context.fillStyle = "#000000";
				__context.font = size + "px " + fontFace;

				glyphRects = new IntMap<GlyphRect>();
				x = y = i = 0;
				continue;

			}

			__context.fillText (c, x + 2, y);
			glyphRects.set(c, new GlyphRect(x, y, width, height, Std.int(width)));

			x += width;

		}

		var image = new js.html.Image ();
		image.src = __canvas.toDataURL();
		return new Image (image, __canvas.width, __canvas.height);*/

		#elseif flash

		/*var bd = new flash.display.BitmapData(128, 128, true, 0);
		var tf = new flash.text.TextField ();
		var format = new flash.text.TextFormat ();
		format.size = size;
		format.font = fontFace;
		tf.defaultTextFormat = format;
		// tf.embedFonts = true;
		var mat = new flash.geom.Matrix ();

		var i = 0, x = 0.0, y = 0.0, maxHeight = 0.0;

		while (i < glyphs.length) {

			var c = glyphs.charAt(i++);
			tf.text = c;

			if (x + tf.textWidth > bd.width) {

				y += maxHeight + 1;
				x = maxHeight = 0;

			}

			if (y + tf.textHeight > bd.height) {

				if (bd.width < bd.height) {

					bd = new flash.display.BitmapData(bd.width * 2, bd.height, true, 0);

				} else {

					bd = new flash.display.BitmapData(bd.width, bd.height * 2, true, 0);

				}

				glyphRects = new IntMap<GlyphRect>();
				x = y = maxHeight = i = 0;
				continue;

			}

			mat.identity ();
			mat.translate (x, y);
			bd.draw (tf, mat);

			glyphRects.set(c, new GlyphRect (x, y, tf.textWidth + 2, tf.textHeight + 2, Std.int(tf.textWidth + 2)));

			x += tf.textWidth + 4;

			if (tf.textHeight + 4 > maxHeight) {

				maxHeight = tf.textHeight + 4;

			}

		}

		return new ImageBuffer (bd, bd.width, bd.height);*/

		#elseif (cpp || neko || nodejs)
		
		if (__handle==null)	throw "Uninitialized font handle.";
		var data = lime_font_create_image (__handle, size, text);
		
		if (data == null) {

			return null;

		} else {
			
			var glyphRects:Map<Int, GlyphRect> = glyphs.get (size);
			
			if (glyphRects == null) {
				
				glyphRects = new Map<Int, GlyphRect>();
				glyphs.set (size, glyphRects);
				
			}
			
			var createdGlyphs:Array<GlyphRect> = [];
			
			var glyphs:Array<Dynamic> = data.glyphs;
			
			for (i in 0 ... glyphs.length)
			{
				
				var gr:GlyphRect = cast glyphs[i];
				glyphRects.set (StringTools.fastCodeAt(text, i), gr);
				createdGlyphs.push(gr);
				
			}
			
			return createdGlyphs;
			
		}

		#end

		return null;

	}


	public function decompose ():NativeFontData {

		#if (cpp || neko || nodejs)
		
		return lime_font_outline_decompose (__handle, 1024 * 1024 * 20);
		
		#else

		return null;

		#end

	}
	
	public function getFontData():NativeFontData {
		
		#if (cpp || neko || nodejs)
		
		if (fontData == null)
			return fontData = lime_font_get_face_info (__handle);
		else
			return fontData;
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function fromBytes (bytes:ByteArray):Font {

		var font = new Font ();
		font.__fromBytes (bytes);
		return font;

	}


	public static function fromFile (path:String):Font {

		var font = new Font ();
		font.__fromFile (path);
		return font;

	}
	
	public static function fromName (name:String):Font {
		
		return fontNames[name];
		
	}


	public function loadRange (size:Int, start:Int, end:Int) {

		#if (flash || js)

		// this.glyphs = glyphs;

		#elseif (cpp || neko || nodejs)
		
		if (__handle==null)	throw "Uninitialized font handle.";
		//lime_font_load_range (__handle, size, start, end);
		
		#end

	}


	public function loadGlyphs (size:Int, glyphs:String=null) {

		if (glyphs == null) {

			glyphs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^`'\"/\\&*()[]{}<>|:;_-+=?,. ";

		}

		#if (flash || html5)

		//this.glyphs = glyphs;

		#elseif (cpp || neko || nodejs)
		
		if (__handle==null)	throw "Uninitialized font handle.";
		//lime_font_load_glyphs (__handle, size, glyphs);
		
		#end

	}


	@:noCompletion private function __fromFile (path:String):Void {

		__fontPath = path;

		#if (cpp || neko || nodejs)

		__handle = lime_font_load (__fontPath);

		if (__handle != null) {

			fontName = lime_font_get_family_name (__handle);
			fontNames[fontName] = this;

		}

		#end

	}
	
	@:noCompletion private function __fromBytes (data:ByteArray):Void {

		#if (cpp || neko || nodejs)

		__handle = lime_font_load (data);

		if (__handle != null) {

			fontName = lime_font_get_family_name (__handle);
			fontNames[fontName] = this;

		}

		#end

	}


	#if (cpp || neko || nodejs)
	private static var lime_font_get_family_name = System.load ("lime", "lime_font_get_family_name", 1);
	private static var lime_font_load:Dynamic->Dynamic = System.load ("lime", "lime_font_load", 1);
	//private static var lime_font_load_glyphs = System.load ("lime", "lime_font_load_glyphs", 3);
	//private static var lime_font_load_range = System.load ("lime", "lime_font_load_range", 4);
	private static var lime_font_create_image = System.load ("lime", "lime_font_create_image", 3);
	private static var lime_font_outline_decompose = System.load ("lime", "lime_font_outline_decompose", 2);
	private static var lime_font_get_face_info = System.load ("lime", "lime_font_get_face_info", 1);
	#end


}


typedef GlyphRect = {
	
	
	public var width:Int;
	public var height:Int;
	public var xOffset:Int;
	public var yOffset:Int;
	public var bitmap:ByteArray;
	
	public var advance:Int;
	public var min_x:Int;
	public var max_x:Int;
	public var min_y:Int;
	public var max_y:Int;

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
