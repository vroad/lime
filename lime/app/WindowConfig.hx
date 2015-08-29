package lime.app;


typedef WindowConfig = { 
	
	@:optional var antialiasing:Int;
	@:optional var background:Int;
	@:optional var borderless:Bool;
	@:optional var depthBuffer:Bool;
	@:optional var display:Int;
	#if (js && html5)
	@:optional var element:#if (haxe_ver >= "3.2") js.html.Element #else js.html.HtmlElement #end;
	#end
	@:optional var fullscreen:Bool;
	@:optional var hardware:Bool;
	@:optional var height:Int;
	@:optional var parameters:String;
	@:optional var resizable:Bool;
	@:optional var stencilBuffer:Bool;
	@:optional var title:String;
	@:optional var vsync:Bool;
	@:optional var width:Int;
	@:optional var x:Int;
	@:optional var y:Int;
	
}