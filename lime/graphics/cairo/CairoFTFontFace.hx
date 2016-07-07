package lime.graphics.cairo;


import lime._internal.graphics.cairo.CairoFontFaceHandle;
import lime.system.CFFIPointer;
import lime.text.Font;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:cffiInterface("CairoFTFontFace.xml")
class CairoFTFontFace extends CairoFontFace {
	
	
	public static inline var FT_LOAD_FORCE_AUTOHINT = (1 << 5);
	
	
	private function new (handle:CairoFontFaceHandle) {
		
		super (handle);
		
	}
	
	
	public static function create (face:Font, loadFlags:Int):CairoFTFontFace {
		
		#if (lime_cairo && !macro)
		var handle = cairo_ft_font_face_create_wrap (face.src, loadFlags);
		return handle != null ? new CairoFTFontFace (handle) : null;
		#else
		return cast 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_ft_font_face_create_wrap (face:CFFIPointer, flags:Int):CairoFontFaceHandle;
	#end
	
	
}