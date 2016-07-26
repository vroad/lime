package lime.graphics.cairo;

import lime._internal.utils.LimeBytes;
import lime.utils.AnonBytes;
import lime.utils.BytesUtil;

import lime._internal.graphics.cairo.CairoSurfaceHandle;
import lime.graphics.ImageBuffer;
import lime.system.CFFIPointer;
import lime.utils.BytesUtil;
import lime.utils.UInt8Array;

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("CairoImageSurface.xml")
class CairoImageSurface extends CairoSurface {
	
	
	public var data (default, null):UInt8Array;
	public var format (get, never):CairoFormat;
	public var height (get, never):Int;
	public var stride (get, never):Int;
	public var width (get, never):Int;
	
	
	private function new (handle:CairoSurfaceHandle) {
		
		super (handle);
		
	}
	
	
	public static function create (data:UInt8Array, format:CairoFormat, width:Int, height:Int, stride:Int):CairoImageSurface {
		
		#if (lime_cairo && !macro)
		var handle = cairo_image_surface_create_for_bytes (BytesUtil.getAnonBytesFromTypedArray (data), format, width, height, stride);
		return handle != null ? new CairoImageSurface (handle) : null;
		#else
		return null;
		#end
		
	}
	
	
	public static function fromImage (image:Image):CairoImageSurface {
		
		#if (lime_cairo && !macro)
		return create (image.buffer.data, CairoFormat.ARGB32, image.width, image.height, image.buffer.stride);
		#else
		return null;
		#end
		
	}
	
	
	// Get & Set Methods
	
	
	@:noCompletion private function get_format ():CairoFormat {
		
		#if (lime_cairo && !macro)
		return cairo_image_surface_get_format (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_height ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_image_surface_get_height (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_stride ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_image_surface_get_stride (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_width ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_image_surface_get_width (handle);
		#else
		return 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_image_surface_create_for_bytes (data:AnonBytes, format:CairoFormat, width:Int, height:Int, stride:Int):CairoSurfaceHandle;
	@:cffi private static function cairo_image_surface_get_format (handle:CairoSurfaceHandle):Int;
	@:cffi private static function cairo_image_surface_get_height (handle:CairoSurfaceHandle):Int;
	@:cffi private static function cairo_image_surface_get_stride (handle:CairoSurfaceHandle):Int;
	@:cffi private static function cairo_image_surface_get_width (handle:CairoSurfaceHandle):Int;
	#end
	
	
}