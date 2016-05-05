package lime.graphics.opengl;
import lime.ui.Window;

#if (js && html5)
typedef GLContextBackend = lime._backend.html5.HTML5GLContext;
#else
typedef GLContextBackend = lime._backend.native.NativeGLContext;
#end

class GLContext {
	
	private var backend:GLContextBackend;
	
	private function new () {
		
	}
	
	public static function create (window:Window):GLContext {
		
		var context:GLContext = new GLContext ();
		context.backend = GLContextBackend.create(window);
		return context;
		
	}
	
	public function makeCurrent (window:Window):Bool {
		
		return backend.makeCurrent (window);
		
	}
	
	public static function clearCurrent ():Bool {
		
		return GLContextBackend.clearCurrent ();
		
	}
	
}