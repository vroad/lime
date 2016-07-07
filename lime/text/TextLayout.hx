package lime.text;


import haxe.io.Bytes;
import lime._internal.text.FontHandle;
import lime._internal.text.TextLayoutHandle;
import lime._internal.utils.CString;
import lime._internal.utils.HaxeBytes;
import lime.math.Vector2;
import lime.system.System;
import lime.utils.AnonBytes;
import lime.utils.BytesUtil;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.text.Font)


@:cffiInterface("TextLayout.xml")
@:cffiCppType("lime::TextLayout")
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
	
	@:noCompletion private var __bytes:AnonBytes;
	@:noCompletion private var __direction:TextDirection;
	@:noCompletion @:cffiHandle private var __handle:TextLayoutHandle;
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
		
		#if (lime_native && !macro)
		__handle = Create (__direction, __script, __language);
		#end
	}
	
	
	@:noCompletion private function __position ():Void {
		
		positions = [];
		
		#if (lime_native && !macro)
		
		if (__handle != null && text != null && text != "" && font != null && font.src != null) {
			
			__bytes = Position (font.src, size, text, __bytes);
			
			var __buffer = BytesUtil.getBytesFromAnonBytes (__bytes);
			var position = 0;
			
			if (__buffer.length > 4) {
				
				var count = __buffer.getInt32 (position); position += 4;
				var index, advanceX, advanceY, offsetX, offsetY;
				
				for (i in 0...count) {
					
					index = __buffer.getInt32 (position); position += 4;
					advanceX = __buffer.getFloat (position); position += 4;
					advanceY = __buffer.getFloat (position); position += 4;
					offsetX = __buffer.getFloat (position); position += 4;
					offsetY = __buffer.getFloat (position); position += 4;
					
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
		
		#if (lime_native && !macro)
		SetDirection (value);
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
		
		#if (lime_native && !macro)
		SetLanguage (value);
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
		
		#if (lime_native && !macro)
		SetScript (value);
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
	
	
	
	
	#if (lime_native && !macro)
	@:cffi private static function Create (direction:Int, script:CString, language:CString):TextLayoutHandle;
	@:cffi private function Position (fontHandle:FontHandle, size:Int, textString:CString, data:HaxeBytes):Dynamic;
	@:cffi private function SetDirection (direction:Int):Void;
	@:cffi private function SetLanguage (language:CString):Void;
	@:cffi private function SetScript (script:CString):Void;
	#end
	
	
}
