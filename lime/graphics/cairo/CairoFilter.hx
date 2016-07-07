package lime.graphics.cairo;


@:cffiCppType("cairo_filter_t")
@:enum abstract CairoFilter(Int) from Int to Int from UInt to UInt {
	
	public var FAST = 0;
	public var GOOD = 1;
	public var BEST = 2;
	public var NEAREST = 3;
	public var BILINEAR = 4;
	public var GAUSSIAN = 5;
	
}