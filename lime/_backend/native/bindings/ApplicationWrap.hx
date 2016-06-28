package lime._backend.native.bindings;
import lime.system.CFFIPointer;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:cffiInterface("lime::Application", "Application_interface.xml")
class ApplicationWrap {
	
	@:cffiHandle public var handle(default, null):CFFIPointer;
	
	#if !macro
	public function new () {
		
		this.handle = Create ();
		
	}
	
	
	@:cffi @:cffiCppType("lime::Application*") private static function Create ():CFFIPointer;
	@:cffi public function Exec ():Int;
	@:cffi public function Init ():Void;
	@:cffi public function Quit ():Int;
	@:cffi public function SetFrameRate (frameRate:Float):Void;
	@:cffi public function Update ():Bool;
	#end
	
}