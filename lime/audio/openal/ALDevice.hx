package lime.audio.openal;


@:allow(lime.audio.openal.AL)
@:allow(lime.audio.openal.ALC)


abstract ALDevice(Null<Float>) from Null<Float> to Null<Float> {
	
	
	private function new (handle:Dynamic) {
		
		this = handle;
		
	}
	
	
}