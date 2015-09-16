package lime.text;

import haxe.io.Bytes;
import lime.math.Vector2;
import lime.system.System;
import lime.utils.ByteArray;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.text.Font)


class TextLayout {
	
	
	public var direction (get, set):TextDirection;
	public var font (default, set):Font;
	public var glyphs (get, null):Array<Glyph>;
	public var language (get, set):String;
	 @:isVar public var positions (get, null):Array<GlyphPosition>;
	public var script (get, set):TextScript;
	public var size (default, set):Int;
	public var text (default, set):String;
	
	private var __dirty:Bool;
	
	@:noCompletion private var __bytes:Dynamic;
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
		
		positions = [];
		__dirty = true;
		
		#if (cpp || neko || nodejs)
		__handle = lime_text_layout_create (__direction, __script, __language);
		#end
	}
	
	
	@:noCompletion private function __position ():Void {
		
		positions = [];
		
		#if (cpp || neko || nodejs)
		
		if (__handle != null && text != null && text != "" && font != null && font.src != null) {
			
			__bytes = lime_text_layout_position (__handle, font.src, size, text, __bytes);
			
			var __buffer = ByteArray.fromBytes (@:privateAccess new Bytes (__bytes.length, #if nodejs __bytes.b.buffer #else __bytes.b #end));
			__buffer.endian = "littleEndian";
			
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
	
	
	
	
	@:noCompletion private function get_positions ():Array<GlyphPosition> {
		
		if (__dirty) {
			
			__dirty = false;
			__position ();
			
		}
		
		return positions;
		
	}
	
	
	@:noCompletion private function get_direction ():TextDirection {
		
		return __direction;
		
	}
	
	
	@:noCompletion private function set_direction (value:TextDirection):TextDirection {
		
		if (value == __direction) return value;
		
		__direction = value;
		
		#if (cpp || neko || nodejs)
		lime_text_layout_set_direction (__handle, value);
		#end
		
		__dirty = true;
		
		return value;
		
	}
	
	
	@:noCompletion private function set_font (value:Font):Font {
		
		if (value == this.font) return value;
		
		this.font = value;
		__dirty = true;
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
		
		__dirty = true;
		
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
		
		__dirty = true;
		
		return value;
		
	}
	
	
	@:noCompletion private function set_size (value:Int):Int {
		
		if (value == this.size) return value;
		
		this.size = value;
		__dirty = true;
		return value;
		
	}
	
	
	@:noCompletion private function set_text (value:String):String {
		
		if (value == this.text) return value;
		
		this.text = value;
		__dirty = true;
		return value;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (cpp || neko || nodejs)
	@:cffi private static function lime_text_layout_create (direction:Int, script:String, language:String):Dynamic;
	@:cffi private static function lime_text_layout_position (textHandle:Float, fontHandle:Float, size:Int, textString:String, data:Dynamic):Dynamic;
	@:cffi private static function lime_text_layout_set_direction (textHandle:Float, direction:Int):Void;
	@:cffi private static function lime_text_layout_set_language (textHandle:Float, language:String):Void;
	@:cffi private static function lime_text_layout_set_script (textHandle:Float, script:String):Void;
	#end
	
	
}
