package lime.graphics.cairo;


@:cffiCppType("cairo_line_cap_t")
@:enum abstract CairoLineCap(Int) from Int to Int from UInt to UInt {
	
	public var BUTT = 0;
	public var ROUND = 1;
	public var SQUARE = 2;
	
}