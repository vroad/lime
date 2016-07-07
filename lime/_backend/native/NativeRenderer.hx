package lime._backend.native;


import haxe.io.Bytes;
import lime._backend.native.opengl.RenderingContext;
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
import lime.graphics.opengl.GL;
import lime.math.Rectangle;
import lime.utils.BytesUtil;
import lime.utils.UInt8Array;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.graphics.cairo.Cairo)
@:access(lime.ui.Window)
@:access(lime.graphics.opengl.GL)


@:cffiInterface("Renderer.xml")
@:cffiCppType("lime::Renderer")
class NativeRenderer {
	
	
	@:cffiHandle public var handle (default, null):Dynamic;
	
	private var parent:Renderer;
	private var glContext:RenderingContext;
	
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
		
		glContext = RenderingContext.create (parent.window.backend.handle);
		
		if (glContext != null) {
			
			handle = null;
			parent.window.__scale = 1;
			
		} else {
			
			handle = Create (parent.window.backend.handle);
			
			if (handle == null) {
				
				throw "Failed to initialize renderer";
				
			}
			
			parent.window.__scale = GetScale ();
			
		}
		
		#if lime_console
		
		parent.context = CONSOLE (ConsoleRenderContext.singleton);
		parent.type = CONSOLE;
		
		#else
		
		if (glContext != null) {
			
			parent.context = OPENGL (glContext);
			parent.type = OPENGL;
			
			GL.context = glContext;
			
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
			
			parent.window.backend.swapWindow ();
			
		} else {
			
			#if lime_cairo
			if (cairo != null) {
				
				primarySurface.flush ();
				
			}
			#end
			
			Unlock ();
			Flip ();
			
		}
		
		#end
		
	}
	
	
	public function readPixels (rect:Rectangle):Image {
		
		#if !macro
		var buffer:ImageBuffer = new ImageBuffer (null, Std.int (rect.width), Std.int (rect.height));
		ReadPixels (buffer, rect);
		return new Image (buffer);
		#else
		return null;
		#end
		
	}
	
	
	public function render ():Void {
		
		#if !macro
		if (glContext == null) {
			
			#if lime_cairo
			var lock:Dynamic = Lock ();
			
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
	@:cffi private static function Create (window:WindowHandle):RendererHandle;
	@:cffi private function Flip ():Void;
	@:cffi private function GetScale ():Float;
	@:cffi private function Lock ():Dynamic;
	@:cffi private function ReadPixels (buffer:ImageBuffer, rect:Rectangle):Void;
	@:cffi private function Unlock ():Void;
	#end
	
	
}


