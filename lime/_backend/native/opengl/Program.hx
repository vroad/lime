package lime._backend.native.opengl;
import lime.system.CFFIPointer;

class Program extends GLObject {
	
	private var shaders(default, null):Array<Shader>;
	
	private function new (id:CFFIPointer) {
		
		super (id);
		shaders = new Array<Shader> ();
		
	}
	
	
	private function attach (shader:Shader):Void {
		
		if (shader != null) {
			
			shaders.push (shader);
			
		}
		
	}
	
	private function detach (shader:Shader):Void {
		
		if (shader != null) {
			
			shaders.remove (shader);
			
		}
		
	}
	
	
	private function getShaders ():Array<Shader> {
		
		return shaders.copy ();
		
	}
	
}