package lime.graphics.cairo;

import lime.utils.BytesUtil;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:forward abstract CairoImageSurface(CairoSurface) from CairoSurface to CairoSurface {
	
	
	public var data (get, never):Dynamic;
	public var format (get, never):CairoFormat;
	public var height (get, never):Int;
	public var stride (get, never):Int;
	public var width (get, never):Int;
	
	
	public function new (format:CairoFormat, width:Int, height:Int):CairoSurface {
		
		#if lime_cairo
		this = lime_cairo_image_surface_create (format, width, height);
		#else
		this = cast 0;
		#end
		
	}
	
	
	public static function create (data:Dynamic, format:CairoFormat, width:Int, height:Int, stride:Int):CairoSurface {
		
		#if lime_cairo
		return lime_cairo_image_surface_create_for_data (data, format, width, height, stride);
		#else
		return cast 0;
		#end
		
	}
	
	
	public static function fromImage (image:Image):CairoSurface {
		
		#if lime_cairo
		return create (lime_bytes_get_data_pointer (BytesUtil.getBytesFromUInt8Array (image.data)), CairoFormat.ARGB32, image.width, image.height, image.buffer.stride);
		#else
		return null;
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private function get_data ():Dynamic {
		
		#if lime_cairo
		return lime_cairo_image_surface_get_data (this);
		#else
		return null;
		#end
		
	}
	
	
	@:noCompletion private function get_format ():CairoFormat {
		
		#if lime_cairo
		return lime_cairo_image_surface_get_format (this);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_height ():Int {
		
		#if lime_cairo
		return lime_cairo_image_surface_get_height (this);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_stride ():Int {
		
		#if lime_cairo
		return lime_cairo_image_surface_get_stride (this);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function get_width ():Int {
		
		#if lime_cairo
		return lime_cairo_image_surface_get_width (this);
		#else
		return 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if lime_cairo
	@:cffi private static function lime_bytes_get_data_pointer (handle:Dynamic):Float;
	@:cffi private static function lime_cairo_image_surface_create (format:Int, width:Int, height:Int):Float;
	@:cffi private static function lime_cairo_image_surface_create_for_data (data:Float, format:Int, width:Int, height:Int, stride:Int):Float;
	@:cffi private static function lime_cairo_image_surface_get_data (handle:Float):Float;
	@:cffi private static function lime_cairo_image_surface_get_format (handle:Float):Int;
	@:cffi private static function lime_cairo_image_surface_get_height (handle:Float):Int;
	@:cffi private static function lime_cairo_image_surface_get_stride (handle:Float):Int;
	@:cffi private static function lime_cairo_image_surface_get_width (handle:Float):Int;
	#end
	
	
}