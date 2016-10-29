package lime.audio.openal;


import lime.system.CFFIPointer;

@:allow(lime.audio.openal.AL)
@:allow(lime.audio.openal.ALC)


class ALContext extends ALObject {
	
	public var device(default, null):ALDevice;
	
	private function new (handle:CFFIPointer, device:ALDevice) {
		
		super (handle);
		this.device = device;
		
	}
	
	
}