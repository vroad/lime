package lime.graphics.cairo;


@:cffiCppType("cairo_content_t")
@:enum abstract CairoContent(Int) from Int to Int from UInt to UInt {
	
	public var COLOR = 0x1000;
	public var ALPHA = 0x2000;
	public var COLOR_ALPHA = 0x3000;
	
}