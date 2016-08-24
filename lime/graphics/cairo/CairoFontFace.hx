package lime.graphics.cairo;


import lime.system.CFFIPointer;
import lime._internal.graphics.cairo.CairoFontFaceHandle;


#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("CairoFontFace.xml")
class CairoFontFace {
	
	@:cffiHandle private var handle:CairoFontFaceHandle;
	
	private function new (handle:CairoFontFaceHandle) {
		
		this.handle = handle;
		
	}
	
	
	public static function create (handle:CFFIPointer):CairoFontFace {
		
		return handle != null ? new CairoFontFace (handle) : null;
		
	}
	
	
	public function status ():CairoStatus {
		
		#if (lime_cairo && lime_cffi && !macro)
		return cairo_font_face_status (handle);
		#else
		return 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_font_face_status (handle:CairoFontFaceHandle):Int;
	#end
	
	
}