package lime.text;


import lime.math.Vector2;
import lime.system.System;
import lime.utils.ByteArray;

@:access(lime.text.Font)


class TextLayout {
	
	
	public var direction (get, set):TextDirection;
	public var font (default, set):Font;
	public var glyphs (get, null):Array<Glyph>;
	public var language (get, set):String;
	public var positions (default, null):Array<GlyphPosition>;
	public var script (get, set):TextScript;
	public var size (default, set):Int;
	public var text (default, set):String;
	
	@:noCompletion private var __buffer:ByteArray;
	@:noCompletion private var __direction:TextDirection;
	@:noCompletion private var __handle:Dynamic;
	@:noCompletion private var __language:String;
	@:noCompletion private var __script:TextScript;
	
	
	public function new (text:String = "", font:Font = null, size:Int = 12, direction:TextDirection = LEFT_TO_RIGHT, script:TextScript = COMMON, language:String = "en") {
		
		this.text = text;
		this.font = font;
		this.size = size;
		__direction = direction;
		__script = script;
		__language = language;
		
		#if (cpp || neko || nodejs)
		__handle = lime_text_layout_create (__direction, __script, __language);
		#end
		
		__position ();
		
	}
	
	
	@:noCompletion private function __position ():Void {
		
		positions = [];
		
		#if (cpp || neko || nodejs)
		
		if (__handle != null && text != null && text != "" && font != null && font.src != null) {
			
			if (__buffer == null) {
				
				__buffer = new ByteArray ();
				__buffer.endian = "littleEndian";
				
			}
			
			lime_text_layout_position (__handle, font.src, size, text, __buffer);
			
			if (__buffer.length > 4) {
				
				__buffer.position = 0;
				
				var count = __buffer.readUnsignedInt ();
				var index, advanceX, advanceY, offsetX, offsetY;
				
				for (i in 0...count) {
					
					index = __buffer.readUnsignedInt ();
					advanceX = __buffer.readFloat ();
					advanceY = __buffer.readFloat ();
					offsetX = __buffer.readFloat ();
					offsetY = __buffer.readFloat ();
					
					positions.push (new GlyphPosition (index, new Vector2 (advanceX, advanceY), new Vector2 (offsetX, offsetY)));
					
				}
				
			}
			
		}
		
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private function get_direction ():TextDirection {
		
		return __direction;
		
	}
	
	
	@:noCompletion private function set_direction (value:TextDirection):TextDirection {
		
		if (value == __direction) return value;
		
		__direction = value;
		
		#if (cpp || neko || nodejs)
		lime_text_layout_set_direction (__handle, value);
		#end
		
		__position ();
		
		return value;
		
	}
	
	
	@:noCompletion private function set_font (value:Font):Font {
		
		if (value == this.font) return value;
		
		this.font = value;
		__position ();
		return value;
		
	}
	
	
	@:noCompletion private function get_glyphs ():Array<Glyph> {
		
		var glyphs = [];
		
		for (position in positions) {
			
			glyphs.push (position.glyph);
			
		}
		
		return glyphs;
		
	}
	
	
	@:noCompletion private function get_language ():String {
		
		return __language;
		
	}
	
	
	@:noCompletion private function set_language (value:String):String {
		
		if (value == __language) return value;
		
		__language = value;
		
		#if (cpp || neko || nodejs)
		lime_text_layout_set_language (__handle, value);
		#end
		
		__position ();
		
		return value;
		
	}
	
	
	@:noCompletion private function get_script ():TextScript {
		
		return __script;
		
	}
	
	
	@:noCompletion private function set_script (value:TextScript):TextScript {
		
		if (value == __script) return value;
		
		__script = value;
		
		#if (cpp || neko || nodejs)
		lime_text_layout_set_script (__handle, value);
		#end
		
		__position ();
		
		return value;
		
	}
	
	
	@:noCompletion private function set_size (value:Int):Int {
		
		if (value == this.size) return value;
		
		this.size = value;
		__position ();
		return value;
		
	}
	
	
	@:noCompletion private function set_text (value:String):String {
		
		if (value == this.text) return value;
		
		this.text = value;
		__position ();
		return value;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (cpp || neko || nodejs)
	private static var lime_text_layout_create = System.load ("lime", "lime_text_layout_create", 3);
	private static var lime_text_layout_position = System.load ("lime", "lime_text_layout_position", 5);
	private static var lime_text_layout_set_direction = System.load ("lime", "lime_text_layout_set_direction", 2);
	private static var lime_text_layout_set_language = System.load ("lime", "lime_text_layout_set_language", 2);
	private static var lime_text_layout_set_script = System.load ("lime", "lime_text_layout_set_script", 2);
	#end
	
	
}