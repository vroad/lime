package lime._backend.native;
import lime._backend.native.NativeWindow;
import lime.graphics.opengl.GLContext;
import lime.ui.Window;

#if !macro
@:build(lime.system.CFFI.build())
#end

class NativeGLContext {
	
	private var handle:Dynamic;
	private var window:NativeWindow;
	
	private function new () {
		
		
		
	}
	
	public static function create (window:Window):NativeGLContext {
		
		var nativeWindow:NativeWindow = @:privateAccess window.backend;
		var handle:Dynamic = lime_gl_context_create (nativeWindow.handle);
		
		if (handle == null) {
			
			return null;
			
		}
		
		var context:NativeGLContext = new NativeGLContext();
		context.handle = handle;
		context.window = nativeWindow;
		return context;
		
	}
	
	public function makeCurrent (window:Window):Bool {
		
		var nativeWindow:NativeWindow = @:privateAccess window.backend;
		return lime_gl_context_make_current (nativeWindow.handle, handle);
		
	}
	
	public static function clearCurrent ():Bool {
		
		return lime_gl_context_clear_current ();
		
	}
	
	#if ((cpp || neko || nodejs) && !macro)
	@:cffi private static function lime_gl_context_create (window:Dynamic):Dynamic;
	@:cffi private static function lime_gl_context_make_current (window:Dynamic, context:Dynamic):Bool;
	@:cffi private static function lime_gl_context_clear_current ():Bool;
	#end
	
}