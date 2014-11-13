package lime.graphics;


import lime.graphics.Image;
import lime.utils.ByteArray;
import lime.utils.UInt8Array;
import lime.system.System;

#if (js && html5)
import js.html.CanvasElement;
import js.html.CanvasRenderingContext2D;
#end

@:autoBuild(lime.Assets.embedFont())


class Font {
	
	
	public var fontName (default, null):String;
	public var image:Image;
	public var glyphs:Map<Int, Map<Int, GlyphRect>>;
	
	@:noCompletion private var __fontPath:String;
	@:noCompletion private var __handle:Dynamic;
	
	
	public function new (fontName:String = null) {
		
		this.fontName = fontName;
		this.glyphs = new Map<Int, Map<Int, GlyphRect>>();
		
	}
	
	
	public function createImage ():ImageBuffer {
		
		glyphs = new Map<Int, Map<Int, GlyphRect>>();
		
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
		
		var data = lime_font_create_image (__handle);
		
		if (data == null) {
			
			return null;
			
		} else {
			
			var glyphRects:Map<Int, GlyphRect>;
			
			for (glyph in cast (data.glyphs, Array<Dynamic>)) {
				
				if (glyphs.exists (glyph.size)) {
					
					glyphRects = glyphs.get (glyph.size);
					
				} else {
					
					glyphRects = new Map<Int, GlyphRect>();
					glyphs.set (glyph.size, glyphRects);
					
				}
				
				glyphRects.set (glyph.codepoint, new GlyphRect (glyph.x, glyph.y, glyph.width, glyph.height, glyph.offset.x, glyph.offset.y));
				
			}
			
			return new ImageBuffer (new UInt8Array (data.image.data), data.image.width, data.image.height, data.image.bpp);
			
		}
		
		#end
		
		return null;
		
	}
	
	
	public function decompose ():NativeFontData {
		
		#if (cpp || neko || nodejs)
		
		return lime_font_outline_decompose (__handle, 1024 * 20);
		
		#else
		
		return null;
		
		#end
		
	}
	
	
	public static function fromBytes (bytes:ByteArray):Font {
		
		var font = new Font ();
		// TODO font.__fromBytes (bytes);
		return font;
		
	}
	
	
	public static function fromFile (path:String):Font {
		
		var font = new Font ();
		font.__fromFile (path);
		return font;
		
	}
	
	
	public function loadRange (size:Int, start:Int, end:Int) {
		
		#if (flash || js)
		
		// this.glyphs = glyphs;
		
		#elseif (cpp || neko || nodejs)
		
		lime_font_load_range (__handle, size, start, end);
		
		#end
		
	}
	
	
	public function loadGlyphs (size:Int, glyphs:String=null) {
		
		if (glyphs == null) {
			
			glyphs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^`'\"/\\&*()[]{}<>|:;_-+=?,. ";
			
		}
		
		#if (flash || js)
		
		//this.glyphs = glyphs;
		
		#elseif (cpp || neko || nodejs)
		
		lime_font_load_glyphs (__handle, size, glyphs);
		
		#end
		
	}
	
	
	@:noCompletion private function __fromFile (path:String):Void {
		
		__fontPath = path;
		
		#if (cpp || neko || nodejs)
		
		__handle = lime_font_load (__fontPath);
		
		if (__handle != null) {
			
			fontName = lime_font_get_family_name (__handle);
			
		}
		
		#end
		
	}
	
	
	#if (cpp || neko || nodejs)
	private static var lime_font_get_family_name = System.load ("lime", "lime_font_get_family_name", 1);
	private static var lime_font_load = System.load ("lime", "lime_font_load", 1);
	private static var lime_font_load_glyphs = System.load ("lime", "lime_font_load_glyphs", 3);
	private static var lime_font_load_range = System.load ("lime", "lime_font_load_range", 4);
	private static var lime_font_create_image = System.load ("lime", "lime_font_create_image", 1);
	private static var lime_font_outline_decompose = System.load ("lime", "lime_font_outline_decompose", 2);
	#end
	
	
}


class GlyphRect {
	
	
	public var x:Float;
	public var y:Float;
	public var width:Float;
	public var height:Float;
	public var xOffset:Int;
	public var yOffset:Int;
	
	
	public function new (x:Float, y:Float, width:Float, height:Float, xOffset:Int=0, yOffset:Int=0) {
		
		this.x = x;
		this.y = y;
		this.xOffset = xOffset;
		this.yOffset = yOffset;
		this.width = width;
		this.height = height;
		
	}
	
	
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