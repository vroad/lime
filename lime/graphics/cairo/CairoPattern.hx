package lime.graphics.cairo;


import lime.math.Matrix3;
import lime.system.CFFIPointer;
import lime._internal.graphics.cairo.CairoMatrixPointer;
import lime._internal.graphics.cairo.CairoPatternHandle;
import lime._internal.graphics.cairo.CairoSurfaceHandle;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.graphics.cairo.CairoSurface)

@:cffiInterface("CairoPattern.xml")
class CairoPattern {
	
	
	private var handle:CairoPatternHandle;
	public var colorStopCount (get, never):Int;
	public var extend (get, set):CairoExtend;
	public var filter (get, set):CairoFilter;
	public var matrix (get, set):Matrix3;
	
	
	private function new (handle:CairoPatternHandle) {
		
		this.handle = handle;
		
	}
	
	
	public static function create (handle:CairoPatternHandle):CairoPattern {
		
		#if (lime_cairo && !macro)
		return handle != null ? new CairoPattern (handle) : null;
		#else
		return null;
		#end
		
	}
	
	
	public function addColorStopRGB (offset:Float, r:Float, g:Float, b:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_pattern_add_color_stop_rgb (handle, offset, r, g, b);
		#end
		
	}
	
	
	public function addColorStopRGBA (offset:Float, r:Float, g:Float, b:Float, a:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_pattern_add_color_stop_rgba (handle, offset, r, g, b, a);
		#end
		
	}
	
	
	public static function createForSurface (surface:CairoSurface):CairoPattern {
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pattern_create_for_surface (surface.handle));
		#else
		return null;
		#end
		
	}
	
	
	public static function createLinear (x0:Float, y0:Float, x1:Float, y1:Float):CairoPattern {
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pattern_create_linear (x0, y0, x1, y1));
		#else
		return null;
		#end
		
	}
	
	
	public static function createRadial (cx0:Float, cy0:Float, radius0:Float, cx1:Float, cy1:Float, radius1:Float):CairoPattern {
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pattern_create_radial (cx0, cy0, radius0, cx1, cy1, radius1));
		#else
		return null;
		#end
		
	}
	
	
	public static function createRGB (r:Float, g:Float, b:Float):CairoPattern {
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pattern_create_rgb (r, g, b));
		#else
		return null;
		#end
		
	}
	
	
	public static function createRGBA (r:Float, g:Float, b:Float, a:Float):CairoPattern {
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pattern_create_rgba (r, g, b, a));
		#else
		return null;
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private function get_colorStopCount ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_pattern_get_color_stop_count_wrap (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_extend ():CairoExtend {
		
		#if (lime_cairo && !macro)
		return cairo_pattern_get_extend (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function set_extend (value:CairoExtend):CairoExtend {
		
		#if (lime_cairo && !macro)
		cairo_pattern_set_extend (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_filter ():CairoFilter {
		
		#if (lime_cairo && !macro)
		return cairo_pattern_get_filter (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function set_filter (value:CairoFilter):CairoFilter {
		
		#if (lime_cairo && !macro)
		cairo_pattern_set_filter (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_matrix ():Matrix3 {
		
		#if (lime_cairo && !macro)
		var m:Dynamic = cairo_pattern_get_matrix_wrap (handle);
		return new Matrix3 (m.a, m.b, m.c, m.d, m.tx, m.ty);
		#else
		return null;
		#end
		
	}
	
	
	@:noCompletion private function set_matrix (value:Matrix3):Matrix3 {
		
		#if (lime_cairo && !macro)
		cairo_pattern_set_matrix (handle, value);
		#end
		
		return value;
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_pattern_add_color_stop_rgb (handle:CairoPatternHandle, offset:Float, red:Float, green:Float, blue:Float):Void;
	@:cffi private static function cairo_pattern_add_color_stop_rgba (handle:CairoPatternHandle, offset:Float, red:Float, green:Float, blue:Float, alpha:Float):Void;
	@:cffi private static function cairo_pattern_create_for_surface (surface:CairoSurfaceHandle):CairoPatternHandle;
	@:cffi private static function cairo_pattern_create_linear (x0:Float, y0:Float, x1:Float, y1:Float):CairoPatternHandle;
	@:cffi private static function cairo_pattern_create_radial (cx0:Float, cy0:Float, radius0:Float, cx1:Float, cy1:Float, radius1:Float):CairoPatternHandle;
	@:cffi private static function cairo_pattern_create_rgb (r:Float, g:Float, b:Float):CairoPatternHandle;
	@:cffi private static function cairo_pattern_create_rgba (r:Float, g:Float, b:Float, a:Float):CairoPatternHandle;
	@:cffi private static function cairo_pattern_get_color_stop_count_wrap (handle:CairoPatternHandle):Int;
	@:cffi private static function cairo_pattern_get_extend (handle:CairoPatternHandle):Int;
	@:cffi private static function cairo_pattern_get_filter (handle:CairoPatternHandle):Int;
	@:cffi private static function cairo_pattern_get_matrix_wrap (handle:CairoPatternHandle):Dynamic;
	@:cffi private static function cairo_pattern_set_extend (handle:CairoPatternHandle, extend:CairoExtend):Void;
	@:cffi private static function cairo_pattern_set_filter (handle:CairoPatternHandle, filter:CairoFilter):Void;
	@:cffi private static function cairo_pattern_set_matrix (handle:CairoPatternHandle, matrix:CairoMatrixPointer):Void;
	#end
	
	
}