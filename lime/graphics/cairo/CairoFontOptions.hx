package lime.graphics.cairo;


import lime.system.CFFIPointer;
import lime.text.Font;
import lime._internal.graphics.cairo.CairoFontOptionsHandle;


#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("CairoFontOptions.xml")
class CairoFontOptions {
	
	private var handle:CairoFontOptionsHandle;
	public var antialias (get, set):CairoAntialias;
	public var hintMetrics (get, set):CairoHintMetrics;
	public var hintStyle (get, set):CairoHintStyle;
	public var subpixelOrder (get, set):CairoSubpixelOrder;
	
	
	private function new (handle:CairoFontOptionsHandle) {
		
		#if (lime_cairo && !macro)
		this.handle = handle;
		#end
		
	}
	
	public static function create ():CairoFontOptions {
		
		#if (lime_cairo && !macro)
		var handle = cairo_font_options_create ();
		return handle != null ? new CairoFontOptions (handle) : null;
		#else
		return null;
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private function get_antialias ():CairoAntialias {
		
		#if (lime_cairo && !macro)
		return cairo_font_options_get_antialias (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_antialias (value:CairoAntialias):CairoAntialias {
		
		#if (lime_cairo && !macro)
		cairo_font_options_set_antialias (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_hintMetrics ():CairoHintMetrics {
		
		#if (lime_cairo && !macro)
		return cairo_font_options_get_hint_metrics (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_hintMetrics (value:CairoHintMetrics):CairoHintMetrics {
		
		#if (lime_cairo && !macro)
		cairo_font_options_set_hint_metrics (handle, value);
		#end
		
		return value;
		
	}
	
	
	
	@:noCompletion private function get_hintStyle ():CairoHintStyle {
		
		#if (lime_cairo && !macro)
		return cairo_font_options_get_hint_style (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_hintStyle (value:CairoHintStyle):CairoHintStyle {
		
		#if (lime_cairo && !macro)
		cairo_font_options_set_hint_style (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_subpixelOrder ():CairoSubpixelOrder {
		
		#if (lime_cairo && !macro)
		return cairo_font_options_get_subpixel_order (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_subpixelOrder (value:CairoSubpixelOrder):CairoSubpixelOrder {
		
		#if (lime_cairo && !macro)
		cairo_font_options_set_subpixel_order (handle, value);
		#end
		
		return value;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cffi && lime_cairo && !macro)
	@:cffi private static function cairo_font_options_create ():CairoFontOptionsHandle;
	@:cffi private static function cairo_font_options_get_antialias (handle:CairoFontOptionsHandle):Int;
	@:cffi private static function cairo_font_options_get_hint_metrics (handle:CairoFontOptionsHandle):Int;
	@:cffi private static function cairo_font_options_get_hint_style (handle:CairoFontOptionsHandle):Int;
	@:cffi private static function cairo_font_options_get_subpixel_order (handle:CairoFontOptionsHandle):Int;
	@:cffi private static function cairo_font_options_set_antialias (handle:CairoFontOptionsHandle, v:CairoAntialias):Void;
	@:cffi private static function cairo_font_options_set_hint_metrics (handle:CairoFontOptionsHandle, v:CairoHintMetrics):Void;
	@:cffi private static function cairo_font_options_set_hint_style (handle:CairoFontOptionsHandle, v:CairoHintStyle):Void;
	@:cffi private static function cairo_font_options_set_subpixel_order (handle:CairoFontOptionsHandle, v:CairoSubpixelOrder):Void;
	#end
	
	
}