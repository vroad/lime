package lime._backend.native.opengl;


import lime.system.CFFIPointer;


class GLObject {
	
	/** The native GL handle/id. read only */
	private var handle (default, null) : CFFIPointer;
	
	private function new (handle:CFFIPointer) {
		
		this.handle = handle;
		
	} //new
	
}