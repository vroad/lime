package lime.audio.openal;


import lime.system.CFFIPointer;

@:allow(lime.audio.openal.AL)
@:allow(lime.audio.openal.ALC)


class ALObject {
	
	/** The native AL handle/id. read only */
	private var handle (default, null) : CFFIPointer;
	
	private function new (handle:CFFIPointer) {
		
		this.handle = handle;
		
	}
	
}