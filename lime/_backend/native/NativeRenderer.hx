package lime._backend.native;


import haxe.io.Bytes;
import lime.graphics.cairo.Cairo;
import lime.graphics.cairo.CairoFormat;
import lime.graphics.cairo.CairoImageSurface;
import lime.graphics.cairo.CairoSurface;
import lime.graphics.CairoRenderContext;
import lime.graphics.ConsoleRenderContext;
import lime.graphics.GLRenderContext;
import lime.graphics.Image;
import lime.graphics.ImageBuffer;
import lime.graphics.Renderer;
import lime.graphics.opengl.GLContext;
import lime.math.Rectangle;
import lime.utils.BytesUtil;
import lime.utils.UInt8Array;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.graphics.cairo.Cairo)
@:access(lime.ui.Window)


class NativeRenderer {
	
	
	public var handle:Dynamic;
	
	private var parent:Renderer;
	private var glContext:GLContext;
	
	#if lime_cairo
	private var cacheLock:Dynamic;
	private var cairo:Cairo;
	private var primarySurface:CairoSurface;
	#end
	
	
	public function new (parent:Renderer) {
		
		this.parent = parent;
		
	}
	
	
	public function create ():Void {
		
		#if !macro
		
		glContext = GLContext.create (parent.window);
		
		if (glContext != null) {
			
			handle = null;
			parent.window.__scale = 1;
			
		} else {
			
			handle = lime_renderer_create (parent.window.backend.handle);
			
			if (handle == null) {
				
				throw "Failed to initialize renderer";
				
			}
			
			parent.window.__scale = lime_renderer_get_scale (handle);
			
		}
		
		#if lime_console
		
		parent.context = CONSOLE (ConsoleRenderContext.singleton);
		parent.type = CONSOLE;
		
		#else
		
		if (glContext != null) {
			
			#if !disable_gl_renderer
			parent.context = OPENGL (new GLRenderContext ());
			parent.type = OPENGL;
			#else
			parent.context = CUSTOM (null);
			parent.type = null;
			#end
			
		} else {
			
			#if lime_cairo
			render ();
			parent.context = CAIRO (cairo);
			#end
			parent.type = CAIRO;
			
		}
		
		#end
		#end
		
	}
	
	
	private function dispatch ():Void {
		
		
		
	}
	
	
	public function flip ():Void {
		
		#if !macro
		
		if (glContext != null) {
			
			lime_gl_swap_window (parent.window.backend.handle);
			
		} else {
			
			#if lime_cairo
			if (cairo != null) {
				
				primarySurface.flush ();
				
			}
			#end
			
			lime_renderer_unlock (handle);
			lime_renderer_flip (handle);
			
		}
		
		#end
		
	}
	
	
	public function readPixels (rect:Rectangle):Image {
		
		var data:Dynamic = lime_renderer_read_pixels (handle, rect);
		
		if (data != null) {
			
			var buffer = new ImageBuffer (BytesUtil.getUInt8ArrayFromAnonBytes (data.data), data.width, data.height, data.bitsPerPixel);
			buffer.format = RGBA32;
			
			return new Image (buffer);
			
		}
		
		return null;
		
	}
	
	
	public function render ():Void {
		
		#if !macro
		if (glContext == null) {
			
			#if lime_cairo
			var lock:Dynamic = lime_renderer_lock (handle);
			
			if (cacheLock == null || cacheLock.pixels != lock.pixels || cacheLock.width != lock.width || cacheLock.height != lock.height) {
				
				primarySurface = CairoImageSurface.create (lock.pixels, CairoFormat.ARGB32, lock.width, lock.height, lock.pitch);
				
				if (cairo != null) {
					
					cairo.recreate (primarySurface);
					
				} else {
					
					cairo = new Cairo (primarySurface);
					
				}
				
			}
			
			cacheLock = lock;
			#else
			parent.context = NONE;
			#end
			
		}
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if !macro
	@:cffi private static function lime_renderer_create (window:Dynamic):Dynamic;
	@:cffi private static function lime_renderer_flip (handle:Dynamic):Void;
	@:cffi private static function lime_renderer_get_scale (handle:Dynamic):Float;
	@:cffi private static function lime_renderer_lock (handle:Dynamic):Dynamic;
	@:cffi private static function lime_renderer_read_pixels (handle:Dynamic, rect:Dynamic):Dynamic;
	@:cffi private static function lime_renderer_unlock (handle:Dynamic):Void;
	
	@:cffi private static function lime_gl_swap_window (window:Dynamic):Void;
	#end
	
	
}


