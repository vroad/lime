package lime.graphics.cairo;


import lime._internal.graphics.cairo.CairoFontFaceHandle;
import lime._internal.graphics.cairo.CairoFontOptionsHandle;
import lime._internal.graphics.cairo.CairoHandle;
import lime._internal.graphics.cairo.CairoMatrixPointer;
import lime._internal.graphics.cairo.CairoPatternHandle;
import lime._internal.graphics.cairo.CairoSurfaceHandle;
import lime._internal.utils.CString;
import lime._internal.utils.DoublePointer;
import lime._internal.utils.HxVector_Double;
import lime.math.Matrix3;
import lime.math.Vector2;
import lime.system.CFFI;
import lime.text.Glyph;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.graphics.cairo.CairoFontFace)
@:access(lime.graphics.cairo.CairoFontOptions)
@:access(lime.graphics.cairo.CairoPattern)
@:access(lime.graphics.cairo.CairoSurface)

@:cffiInterface("Cairo_Interface.xml")
class Cairo {
	
	
	public static var version (get, null):Int;
	public static var versionString (get, null):String;
	
	public var antialias (get, set):CairoAntialias;
	public var currentPoint (get, never):Vector2;
	public var dash (get, set):Array<Float>;
	public var dashCount (get, never):Int;
	public var fillRule (get, set):CairoFillRule;
	public var fontFace (get, set):CairoFontFace;
	public var fontOptions (get, set):CairoFontOptions;
	public var groupTarget (get, never):CairoSurface;
	public var hasCurrentPoint (get, never):Bool;
	public var lineCap (get, set):CairoLineCap;
	public var lineJoin (get, set):CairoLineJoin;
	public var lineWidth (get, set):Float;
	public var matrix (get, set):Matrix3;
	public var miterLimit (get, set):Float;
	public var operator (get, set):CairoOperator;
	public var source (get, set):CairoPattern;
	public var target (default, null):CairoSurface;
	public var tolerance (get, set):Float;
	public var userData:Dynamic;
	
	@:noCompletion private var handle:CairoHandle;
	private var __fontFace:CairoFontFace;
	private var __fontOptions:CairoFontOptions;
	private var __groupTarget:CairoSurface;
	private var __source:CairoPattern;
	
	public function new (surface:CairoSurface = null):Void {
		
		if (surface != null) {
			
			#if (lime_cairo && !macro)
			handle = cairo_create (surface.handle);
			#end
			
		}
		
		target = surface;
		
	}
	
	
	public function arc (xc:Float, yc:Float, radius:Float, angle1:Float, angle2:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_arc (handle, xc, yc, radius, angle1, angle2);
		#end
		
	}
	
	
	public function arcNegative (xc:Float, yc:Float, radius:Float, angle1:Float, angle2:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_arc_negative (handle, xc, yc, radius, angle1, angle2);
		#end
		
	}
	
	
	public function clip ():Void {
		
		#if (lime_cairo && !macro)
		cairo_clip (handle);
		#end
		
	}
	
	
	public function clipExtents (x1:Float, y1:Float, x2:Float, y2:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_clip_extents (handle, x1, y1, x2, y2);
		#end
		
	}
	
	
	public function clipPreserve ():Void {
		
		#if (lime_cairo && !macro)
		cairo_clip_preserve (handle);
		#end
		
	}
	
	
	public function closePath ():Void {
		
		#if (lime_cairo && !macro)
		cairo_close_path (handle);
		#end
		
	}
	
	
	public function copyPage ():Void {
		
		#if (lime_cairo && !macro)
		cairo_copy_page (handle);
		#end
		
	}
	
	
	public function curveTo (x1:Float, y1:Float, x2:Float, y2:Float, x3:Float, y3:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_curve_to (handle, x1, y1, x2, y2, x3, y3);
		#end
		
	}
	
	
	public function fill ():Void {
		
		#if (lime_cairo && !macro)
		cairo_fill (handle);
		#end
		
	}
	
	
	public function fillExtents (x1:Float, y1:Float, x2:Float, y2:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_fill_extents (handle, x1, y1, x2, y2);
		#end
		
	}
	
	
	public function fillPreserve ():Void {
		
		#if (lime_cairo && !macro)
		cairo_fill_preserve (handle);
		#end
		
	}
	
	
	public function identityMatrix ():Void {
		
		#if (lime_cairo && !macro)
		cairo_identity_matrix (handle);
		#end
		
	}
	
	
	public function inClip (x:Float, y:Float):Bool {
		
		#if (lime_cairo && !macro)
		return cairo_in_clip (handle, x, y);
		#else
		return false;
		#end
		
	}
	
	
	public function inFill (x:Float, y:Float):Bool {
		
		#if (lime_cairo && !macro)
		return cairo_in_fill (handle, x, y);
		#else
		return false;
		#end
		
	}
	
	
	public function inStroke (x:Float, y:Float):Bool {
		
		#if (lime_cairo && !macro)
		return cairo_in_stroke (handle, x, y);
		#else
		return false;
		#end
		
	}
	
	
	public function lineTo (x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_line_to (handle, x, y);
		#end
		
	}
	
	
	public function moveTo (x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_move_to (handle, x, y);
		#end
		
	}
	
	
	public function mask (pattern:CairoPattern):Void {
		
		#if (lime_cairo && !macro)
		cairo_mask (handle, pattern.handle);
		#end
		
	}
	
	
	public function maskSurface (surface:CairoSurface, x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_mask_surface (handle, surface.handle, x, y);
		#end
		
	}
	
	
	public function newPath ():Void {
		
		#if (lime_cairo && !macro)
		cairo_new_path (handle);
		#end
		
	}
	
	
	public function paint ():Void {
		
		#if (lime_cairo && !macro)
		cairo_paint (handle);
		#end
		
	}
	
	
	public function paintWithAlpha (alpha:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_paint_with_alpha (handle, alpha);
		#end
		
	}
	
	
	public function popGroup ():CairoPattern {
		
		__groupTarget = null;
		
		#if (lime_cairo && !macro)
		return new CairoPattern (cairo_pop_group (handle));
		#else
		return null;
		#end
		
	}
	
	
	public function popGroupToSource ():Void {
		
		__groupTarget = null;
		
		#if (lime_cairo && !macro)
		cairo_pop_group_to_source (handle);
		#end
		
	}
	
	
	public function pushGroup ():Void {
		
		__groupTarget = null;
		
		#if (lime_cairo && !macro)
		cairo_push_group (handle);
		#end
		
	}
	
	
	public function pushGroupWithContent (content:CairoContent):Void {
		
		__groupTarget = null;
		
		#if (lime_cairo && !macro)
		cairo_push_group_with_content (handle, content);
		#end
		
	}
	
	
	private function recreate (surface:CairoSurface):Void {
		
		#if (lime_cairo && !macro)
		handle = cairo_create (surface.handle);
		#end
	}
	
	
	public function rectangle (x:Float, y:Float, width:Float, height:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_rectangle (handle, x, y, width, height);
		#end
		
	}
	
	
	public function relCurveTo (dx1:Float, dy1:Float, dx2:Float, dy2:Float, dx3:Float, dy3:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_rel_curve_to (handle, dx1, dy1, dx2, dy2, dx3, dy3);
		#end
		
	}
	
	
	public function relLineTo (dx:Float, dy:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_rel_line_to (handle, dx, dy);
		#end
		
	}
	
	
	public function relMoveTo (dx:Float, dy:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_rel_move_to (handle, dx, dy);
		#end
		
	}
	
	
	public function resetClip ():Void {
		
		#if (lime_cairo && !macro)
		cairo_reset_clip (handle);
		#end
		
	}
	
	
	public function restore ():Void {
		
		#if (lime_cairo && !macro)
		cairo_restore (handle);
		#end
		
	}
	
	
	public function save ():Void {
		
		#if (lime_cairo && !macro)
		cairo_save (handle);
		#end
		
	}
	
	
	public function setFontSize (size:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_set_font_size_wrap (handle, size);
		#end
		
	}
	
	
	public function setSourceRGB (r:Float, g:Float, b:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_set_source_rgb (handle, r, g, b);
		#end
		
	}
	
	
	public function setSourceRGBA (r:Float, g:Float, b:Float, a:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_set_source_rgba (handle, r, g, b, a);
		#end
		
	}
	
	
	public function setSourceSurface (surface:CairoSurface, x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_set_source_surface (handle, surface.handle, x, y);
		#end
		
	}
	
	
	public function showGlyphs (glyphs:Array<CairoGlyph>):Void {
		
		#if (lime_cairo && !macro)
		cairo_show_glyphs_wrap (handle, glyphs);
		#end
		
	}
	
	
	public function showPage ():Void {
		
		#if (lime_cairo && !macro)
		cairo_show_page (handle);
		#end
		
	}
	
	
	public function showText (utf8:String):Void {
		
		#if (lime_cairo && !macro)
		cairo_show_text (handle, utf8);
		#end
		
	}
	
	
	public function status ():CairoStatus {
		
		#if (lime_cairo && !macro)
		return cairo_status (handle);
		#else
		return cast 0;
		#end
		
	}
	
	
	public function stroke ():Void {
		
		#if (lime_cairo && !macro)
		cairo_stroke (handle);
		#end
		
	}
	
	
	public function strokeExtents (x1:Float, y1:Float, x2:Float, y2:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_stroke_extents (handle, x1, y1, x2, y2);
		#end
		
	}
	
	
	public function strokePreserve ():Void {
		
		#if (lime_cairo && !macro)
		cairo_stroke_preserve (handle);
		#end
		
	}
	
	
	public function transform (matrix:Matrix3):Void {
		
		#if (lime_cairo && !macro)
		cairo_transform (handle, matrix);
		#end
		
	}
	
	public function rotate (amount:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_rotate (handle, amount);
		#end
		
	}
	
	public function scale (x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_scale (handle, x, y);
		#end
		
	}
	
	
	public function translate (x:Float, y:Float):Void {
		
		#if (lime_cairo && !macro)
		cairo_translate (handle, x, y);
		#end
		
	}
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private function get_antialias ():CairoAntialias {
		
		#if (lime_cairo && !macro)
		return cairo_get_antialias (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_antialias (value:CairoAntialias):CairoAntialias {
		
		#if (lime_cairo && !macro)
		cairo_set_antialias (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_currentPoint ():Vector2 {
		
		#if (lime_cairo && !macro)
		var vec:Dynamic = cairo_get_current_point_wrap (handle);
		return new Vector2 (vec.x, vec.y);
		#end
		
		return null;
		
	}
	
	
	@:noCompletion private function get_dash ():Array<Float> {
		
		#if (lime_cairo && !macro)
		var result:Dynamic = cairo_get_dash_wrap (handle);
		return result;
		#end
		
		return [];
		
	}
	
	
	@:noCompletion private function set_dash (value:Array<Float>):Array<Float> {
		
		#if (lime_cairo && !macro)
		cairo_set_dash_wrap (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_dashCount ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_get_dash_count (handle);
		#end
		
		return 0;
		
	}
	
	
	@:noCompletion private function get_fillRule ():CairoFillRule {
		
		#if (lime_cairo && !macro)
		return cairo_get_fill_rule (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_fillRule (value:CairoFillRule):CairoFillRule {
		
		#if (lime_cairo && !macro)
		cairo_set_fill_rule (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_fontFace ():CairoFontFace {
		
		if (__fontFace == null) {
			
			#if (lime_cairo && !macro)
			__fontFace = CairoFontFace.create (cairo_get_font_face_wrap (handle));
			#end
			
		}
		
		return __fontFace;
		
	}
	
	
	@:noCompletion private function set_fontFace (value:CairoFontFace):CairoFontFace {
		
		if (__fontFace != value) {
			
			#if (lime_cairo && !macro)
			cairo_set_font_face (handle, value.handle);
			#end
			
			__fontFace = value;
			
		}
		
		return value;
		
	}
	
	
	@:noCompletion private function get_fontOptions ():CairoFontOptions {
		
		#if (lime_cairo && !macro)
		if (__fontOptions == null) {
			
			__fontOptions = new CairoFontOptions (cairo_get_font_options_wrap (handle));
			
		}
		
		return __fontOptions;
		#else
		return null;
		#end
		
	}
	
	
	@:noCompletion private function set_fontOptions (value:CairoFontOptions):CairoFontOptions {
		
		if (__fontOptions != value) {
			
			#if (lime_cairo && !macro)
			cairo_set_font_options (handle, value.handle);
			#end
			__fontOptions = value;
			
		}
		
		return value;
		
	}
	
	
	@:noCompletion private function get_groupTarget ():CairoSurface {
		
		if (__groupTarget == null) {
			
			#if (lime_cairo && !macro)
			__groupTarget = new CairoSurface (cairo_get_group_target (handle));
			#end
			
		}
		
		return __groupTarget;
		
	}
	
	
	@:noCompletion private function get_hasCurrentPoint ():Bool {
		
		#if (lime_cairo && !macro)
		return cairo_has_current_point (handle);
		#end
		
		return false;
		
	}
	
	
	@:noCompletion private function get_lineCap ():CairoLineCap {
		
		#if (lime_cairo && !macro)
		return cairo_get_line_cap (handle);
		#end
		
		return 0;
		
	}
	
	
	@:noCompletion private function set_lineCap (value:CairoLineCap):CairoLineCap {
		
		#if (lime_cairo && !macro)
		cairo_set_line_cap (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_lineJoin ():CairoLineJoin {
		
		#if (lime_cairo && !macro)
		return cairo_get_line_join (handle);
		#end
		
		return 0;
		
	}
	
	
	@:noCompletion private function set_lineJoin (value:CairoLineJoin):CairoLineJoin {
		
		#if (lime_cairo && !macro)
		cairo_set_line_join (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_lineWidth ():Float {
		
		#if (lime_cairo && !macro)
		return cairo_get_line_width (handle);
		#end
		
		return 0;
		
	}
	
	
	@:noCompletion private function set_lineWidth (value:Float):Float {
		
		#if (lime_cairo && !macro)
		cairo_set_line_width (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_matrix ():Matrix3 {
		
		#if (lime_cairo && !macro)
		var m:Dynamic = cairo_get_matrix_wrap (handle);
		return new Matrix3 (m.a, m.b, m.c, m.d, m.tx, m.ty);
		#end
		
		return null;
		
	}
	
	
	@:noCompletion private function set_matrix (value:Matrix3):Matrix3 {
		
		#if (lime_cairo && !macro)
		cairo_set_matrix_wrap (handle, value.a, value.b, value.c, value.d, value.tx, value.ty);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_miterLimit ():Float {
		
		#if (lime_cairo && !macro)
		return cairo_get_miter_limit (handle);
		#end
		
		return 0;
		
	}
	
	
	@:noCompletion private function set_miterLimit (value:Float):Float {
		
		#if (lime_cairo && !macro)
		cairo_set_miter_limit (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_operator ():CairoOperator {
		
		#if (lime_cairo && !macro)
		return cairo_get_operator (handle);
		#end
		
		return cast 0;
		
	}
	
	
	@:noCompletion private function set_operator (value:CairoOperator):CairoOperator {
		
		#if (lime_cairo && !macro)
		cairo_set_operator (handle, value);
		#end
		
		return value;
		
	}
	
	
	@:noCompletion private function get_source ():CairoPattern {
		
		#if (lime_cairo && !macro)
		if (__source == null) {
			
			__source = new CairoPattern (cairo_get_source_wrap (handle));
			
		}
		#end
		
		return __source;
		
	}
	
	
	@:noCompletion private function set_source (value:CairoPattern):CairoPattern {
		
		if (__source != value) {
			
			#if (lime_cairo && !macro)
			cairo_set_source (handle, value.handle);
			#end
			
			__source = value;
			
		}
		
		return value;
		
	}
	
	
	@:noCompletion private function get_tolerance ():Float {
		
		#if (lime_cairo && !macro)
		return cairo_get_tolerance (handle);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private function set_tolerance (value:Float):Float {
		
		#if (lime_cairo && !macro)
		cairo_set_tolerance (handle, value);
		#end
		
		return value;
		
	}
	
	
	private static function get_version ():Int {
		
		#if (lime_cairo && !macro)
		return cairo_version ();
		#else
		return 0;
		#end
		
	}
	
	
	private static function get_versionString ():String {
		
		#if (lime_cairo && !macro)
		return cairo_version_string ();
		#else
		return "";
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_cairo && !macro)
	@:cffi private static function cairo_arc (handle:CairoHandle, xc:Float, yc:Float, radius:Float, angle1:Float, angle2:Float):Void;
	@:cffi private static function cairo_arc_negative (handle:CairoHandle, xc:Float, yc:Float, radius:Float, angle1:Float, angle2:Float):Void;
	@:cffi private static function cairo_clip (handle:CairoHandle):Void;
	@:cffi private static function cairo_clip_preserve (handle:CairoHandle):Void;
	@:cffi private static function cairo_clip_extents (handle:CairoHandle, x1:DoublePointer, y1:DoublePointer, x2:DoublePointer, y2:DoublePointer):Void;
	@:cffi private static function cairo_close_path (handle:CairoHandle):Void;
	@:cffi private static function cairo_copy_page (handle:CairoHandle):Void;
	@:cffi private static function cairo_create (handle:CairoSurfaceHandle):CairoHandle;
	@:cffi private static function cairo_curve_to (handle:CairoHandle, x1:Float, y1:Float, x2:Float, y2:Float, x3:Float, y3:Float):Void;
	@:cffi private static function cairo_fill (handle:CairoHandle):Void;
	@:cffi private static function cairo_fill_extents (handle:CairoHandle, x1:DoublePointer, y1:DoublePointer, x2:DoublePointer, y2:DoublePointer):Void;
	@:cffi private static function cairo_fill_preserve (handle:CairoHandle):Void;
	@:cffi private static function cairo_get_antialias (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_current_point_wrap (handle:CairoHandle):Dynamic;
	@:cffi private static function cairo_get_dash_wrap (handle:CairoHandle):Dynamic;
	@:cffi private static function cairo_get_dash_count (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_fill_rule (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_font_face_wrap (handle:CairoHandle):CairoFontFaceHandle;
	@:cffi private static function cairo_get_font_options_wrap (handle:CairoHandle):CairoFontOptionsHandle;
	@:cffi private static function cairo_get_group_target (handle:CairoHandle):CairoSurfaceHandle;
	@:cffi private static function cairo_get_line_cap (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_line_join (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_line_width (handle:CairoHandle):Float;
	@:cffi private static function cairo_get_matrix_wrap (handle:CairoHandle):Dynamic;
	@:cffi private static function cairo_get_miter_limit (handle:CairoHandle):Float;
	@:cffi private static function cairo_get_operator (handle:CairoHandle):Int;
	@:cffi private static function cairo_get_source_wrap (handle:CairoHandle):CairoPatternHandle;
	@:cffi private static function cairo_get_target (handle:CairoHandle):CairoSurfaceHandle;
	@:cffi private static function cairo_get_tolerance (handle:CairoHandle):Float;
	@:cffi private static function cairo_has_current_point (handle:CairoHandle):Bool;
	@:cffi private static function cairo_identity_matrix (handle:CairoHandle):Void;
	@:cffi private static function cairo_in_clip (handle:CairoHandle, x:Float, y:Float):Bool;
	@:cffi private static function cairo_in_fill (handle:CairoHandle, x:Float, y:Float):Bool;
	@:cffi private static function cairo_in_stroke (handle:CairoHandle, x:Float, y:Float):Bool;
	@:cffi private static function cairo_line_to (handle:CairoHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_mask (handle:CairoHandle, pattern:CairoPatternHandle):Void;
	@:cffi private static function cairo_mask_surface (handle:CairoHandle, surface:CairoSurfaceHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_move_to (handle:CairoHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_new_path (handle:CairoHandle):Void;
	@:cffi private static function cairo_paint (handle:CairoHandle):Void;
	@:cffi private static function cairo_paint_with_alpha (handle:CairoHandle, alpha:Float):Void;
	@:cffi private static function cairo_pop_group (handle:CairoHandle):CairoPatternHandle;
	@:cffi private static function cairo_pop_group_to_source (handle:CairoHandle):Void;
	@:cffi private static function cairo_push_group (handle:CairoHandle):Void;
	@:cffi private static function cairo_push_group_with_content (handle:CairoHandle, content:CairoContent):Void;
	@:cffi private static function cairo_rectangle (handle:CairoHandle, x:Float, y:Float, width:Float, height:Float):Void;
	@:cffi private static function cairo_rel_curve_to (handle:CairoHandle, dx1:Float, dy1:Float, dx2:Float, dy2:Float, dx3:Float, dy3:Float):Void;
	@:cffi private static function cairo_rel_line_to (handle:CairoHandle, dx:Float, dy:Float):Void;
	@:cffi private static function cairo_rel_move_to (handle:CairoHandle, dx:Float, dy:Float):Void;
	@:cffi private static function cairo_reset_clip (handle:CairoHandle):Void;
	@:cffi private static function cairo_restore (handle:CairoHandle):Void;
	@:cffi private static function cairo_rotate (handle:CairoHandle, amount:Float):Void;
	@:cffi private static function cairo_save (handle:CairoHandle):Void;
	@:cffi private static function cairo_scale (handle:CairoHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_set_antialias (handle:CairoHandle, cap:CairoAntialias):Void;
	@:cffi private static function cairo_set_dash_wrap (handle:CairoHandle, dash:HxVector_Double):Void;
	@:cffi private static function cairo_set_fill_rule (handle:CairoHandle, cap:CairoFillRule):Void;
	@:cffi private static function cairo_set_font_face (handle:CairoHandle, face:CairoFontFaceHandle):Void;
	@:cffi private static function cairo_set_font_options (handle:CairoHandle, options:CairoFontOptionsHandle):Void;
	@:cffi private static function cairo_set_font_size_wrap (handle:CairoHandle, size:Float):Void;
	@:cffi private static function cairo_set_line_cap (handle:CairoHandle, cap:CairoLineCap):Void;
	@:cffi private static function cairo_set_line_join (handle:CairoHandle, join:CairoLineJoin):Void;
	@:cffi private static function cairo_set_line_width (handle:CairoHandle, width:Float):Void;
	@:cffi private static function cairo_set_matrix_wrap (handle:CairoHandle, a:Float, b:Float, c:Float, d:Float, tx:Float, ty:Float):Void;
	@:cffi private static function cairo_set_miter_limit (handle:CairoHandle, miterLimit:Float):Void;
	@:cffi private static function cairo_set_operator (handle:CairoHandle, op:CairoOperator):Void;
	@:cffi private static function cairo_set_source (handle:CairoHandle, pattern:CairoPatternHandle):Void;
	@:cffi private static function cairo_set_source_rgb (handle:CairoHandle, r:Float, g:Float, b:Float):Void;
	@:cffi private static function cairo_set_source_rgba (handle:CairoHandle, r:Float, g:Float, b:Float, a:Float):Void;
	@:cffi private static function cairo_set_source_surface (handle:CairoHandle, surface:CairoSurfaceHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_set_tolerance (handle:CairoHandle, tolerance:Float):Void;
	@:cffi private static function cairo_show_glyphs_wrap (handle:CairoHandle, glyphs:Dynamic):Void;
	@:cffi private static function cairo_show_page (handle:CairoHandle):Void;
	@:cffi private static function cairo_show_text (handle:CairoHandle, text:CString):Void;
	@:cffi private static function cairo_status (handle:CairoHandle):Int;
	@:cffi private static function cairo_stroke (handle:CairoHandle):Void;
	@:cffi private static function cairo_stroke_extents (handle:CairoHandle, x1:DoublePointer, y1:DoublePointer, x2:DoublePointer, y2:DoublePointer):Void;
	@:cffi private static function cairo_stroke_preserve (handle:CairoHandle):Void;
	@:cffi private static function cairo_transform (handle:CairoHandle, matrix:CairoMatrixPointer):Void;
	@:cffi private static function cairo_translate (handle:CairoHandle, x:Float, y:Float):Void;
	@:cffi private static function cairo_version ():Int;
	@:cffi private static function cairo_version_string ():CString;
	#end
	
	
}