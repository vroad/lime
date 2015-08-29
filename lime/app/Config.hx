package lime.app;


typedef Config = {
	
	#if (js && html5)
	@:optional var assetsPrefix:String;
	#end
	@:optional var build:String;
	@:optional var company:String;
	@:optional var file:String;
	@:optional var fps:Int;
	@:optional var name:String;
	@:optional var orientation:String;
	@:optional var packageName:String;
	@:optional var version:String;
	@:optional var windows:Array<WindowConfig>;
	
}