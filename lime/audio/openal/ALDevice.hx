package lime.audio.openal;


import lime.system.CFFIPointer;

@:allow(lime.audio.openal.AL)
@:allow(lime.audio.openal.ALC)


class ALDevice extends ALObject {
	
	
	private function new (handle:CFFIPointer) {
		
		super (handle);
		
	}
	
	
}