package lime.graphics.cairo;


import lime.system.CFFIPointer;
import lime._internal.graphics.cairo.CairoSurfaceHandle;


#if !macro
@:build(lime.system.CFFI.build())
#end

@:cffiInterface("CairoSurface.xml")
class CairoSurface {
	
	
	private var handle:CairoSurfaceHandle;
	
	
	private function new (handle:CairoSurfaceHandle) {
		
		#if (lime_cairo && !macro)
		this.handle = handle;
		#end
		
	}
	
	
	public function flush ():Void {
		
		#if (lime_cairo && !macro)
		cairo_surface_flush (handle);
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_surface_flush (surface:CairoSurfaceHandle):Void;
	#end
	
	
}