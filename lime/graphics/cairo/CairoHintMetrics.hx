package lime.graphics.cairo;


@:cffiCppType("cairo_hint_metrics_t")
@:enum abstract CairoHintMetrics(Int) from Int to Int from UInt to UInt {
	
	public var DEFAULT = 0;
	public var OFF = 1;
	public var ON = 2;
	
}