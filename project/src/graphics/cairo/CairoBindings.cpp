#include <cairo.h>
#include <cairo-ft.h>
#include <math/Matrix3.h>
#include <math/Vector2.h>
//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <text/Font.h>

#include <utils/PointerWrapper.h>
#include <utils/Kinds.h>

namespace lime {
	
	void gc_cairo (value handle);
	void gc_cairo_font_face (value handle);
	void gc_cairo_pattern (value handle);
	void gc_cairo_font_options (value handle);
	void gc_cairo_surface (value handle);
	
	cairo_t *val_to_cairo_t (value handle) {
		
		return (cairo_t*)val_to_kind (handle, GetKinds ().cairo_t);
		
	}
	
	cairo_surface_t *val_to_cairo_surface_t (value handle) {
		
		return (cairo_surface_t*)val_to_kind (handle, GetKinds ().cairo_surface_t);
		
	}
	
	cairo_font_face_t *val_to_cairo_font_face_t (value handle) {
		
		return (cairo_font_face_t*)val_to_kind (handle, GetKinds ().cairo_font_face_t);
		
	}
	
	cairo_pattern_t *val_to_cairo_pattern_t (value handle) {
		
		return (cairo_pattern_t*)val_to_kind (handle, GetKinds ().cairo_pattern_t);
		
	}
	
	cairo_font_options_t *val_to_cairo_font_options_t (value handle) {
		
		return (cairo_font_options_t*)val_to_kind (handle, GetKinds ().cairo_font_options_t);
		
	}
	
	Font *val_to_Font (value handle) {
		
		return (Font*)val_to_kind (handle, GetKinds ().Font);
		
	}

	value cairo_t_to_value (cairo_t *cairo, bool setFinalizer = false) {
		
		value outValue = WrapPointerInternal<cairo_t> (cairo, GetKinds ().cairo_t);
		if (setFinalizer)
			val_gc (outValue, gc_cairo);
		return outValue;
		
	}
	
	value cairo_surface_t_to_value (cairo_surface_t *surface, bool setFinalizer = false) {
		
		value outValue = WrapPointerInternal<cairo_surface_t> (surface, GetKinds ().cairo_surface_t);
		if (setFinalizer)
			val_gc (outValue, gc_cairo_surface);
		return outValue;
		
	}
	
	value cairo_font_options_t_to_value (cairo_font_options_t *options, bool setFinalizer = false) {
		
		value outValue = WrapPointerInternal<cairo_font_options_t> (options, GetKinds ().cairo_font_options_t);
		if (setFinalizer)
			val_gc (outValue, gc_cairo_font_options);
		return outValue;
		
	}
	
	value cairo_font_face_t_to_value (cairo_font_face_t *font_face, bool setFinalizer = false) {
		
		value outValue = WrapPointerInternal<cairo_font_face_t> (font_face, GetKinds ().cairo_font_face_t);
		if (setFinalizer)
			val_gc (outValue, gc_cairo_font_face);
		return outValue;
		
	}
	
	value cairo_pattern_t_to_value (cairo_pattern_t *pattern, bool setFinalizer = false) {
		
		value outValue = WrapPointerInternal<cairo_pattern_t> (pattern, GetKinds ().cairo_pattern_t);
		if (setFinalizer)
			val_gc (outValue, gc_cairo_pattern);
		return outValue;
		
	}
	
	
	cairo_user_data_key_t userData;
	
	
	void gc_cairo (value handle) {
		
		if (!val_is_null (handle)) {
			
			cairo_t* cairo = (cairo_t*)val_data (handle);
			cairo_destroy (cairo);
			//free_abstract (handle);
			
		}
		
	}
	
	
	void gc_cairo_font_face (value handle) {
		
		if (!val_is_null (handle)) {
			
			cairo_font_face_t* face = (cairo_font_face_t*)val_data (handle);
			cairo_font_face_destroy (face);
			//free_abstract (handle);
			
		}
		
	}
	
	
	void gc_cairo_font_options (value handle) {
		
		if (!val_is_null (handle)) {
			
			cairo_font_options_t* options = (cairo_font_options_t*)val_data (handle);
			cairo_font_options_destroy (options);
			//free_abstract (handle);
			
		}
		
	}
	
	
	void gc_cairo_pattern (value handle) {
		
		if (!val_is_null (handle)) {
			
			cairo_pattern_t* pattern = (cairo_pattern_t*)val_data (handle);
			cairo_pattern_destroy (pattern);
			//free_abstract (handle);
			
		}
		
	}
	
	
	void gc_cairo_surface (value handle) {
		
		if (!val_is_null (handle)) {
			
			cairo_surface_t* surface = (cairo_surface_t*)val_data (handle);
			cairo_surface_destroy (surface);
			//free_abstract (handle);
			
		}
		
	}
	
	
	void gc_user_data (void* data) {
		
		AutoGCRoot* reference = (AutoGCRoot*)data;
		delete reference;
		
	}
	
	
	void lime_cairo_arc (value handle, double xc, double yc, double radius, double angle1, double angle2) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_arc (cairo, xc, yc, radius, angle1, angle2);
		
	}
	
	
	void lime_cairo_arc_negative (value handle, double xc, double yc, double radius, double angle1, double angle2) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_arc_negative (cairo, xc, yc, radius, angle1, angle2);
		
	}
	
	
	void lime_cairo_clip (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_clip (cairo);
		
	}
	
	
	void lime_cairo_clip_extents (value handle, double x1, double y1, double x2, double y2) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_clip_extents (cairo, &x1, &y1, &x2, &y2);
		
	}
	
	
	void lime_cairo_clip_preserve (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_clip_preserve (cairo);
		
	}
	
	
	void lime_cairo_close_path (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_close_path (cairo);
		
	}
	
	
	void lime_cairo_copy_page (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_copy_page (cairo);
		
	}
	
	
	value lime_cairo_create (value inSurface) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (inSurface);
		return cairo_t_to_value (cairo_create (surface), true);
		
	}
	
	
	void lime_cairo_curve_to (value handle, double x1, double y1, double x2, double y2, double x3, double y3) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_curve_to (cairo, x1, y1, x2, y2, x3, y3);
		
	}
	
	
	void lime_cairo_destroy (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_destroy (cairo);
		free_abstract (handle);
		
	}
	
	
	void lime_cairo_fill (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_fill (cairo);
		
	}
	
	
	void lime_cairo_fill_extents (value handle, double x1, double y1, double x2, double y2) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_fill_extents (cairo, &x1, &y1, &x2, &y2);
		
	}
	
	
	void lime_cairo_fill_preserve (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_fill_preserve (cairo);
		
	}
	
	
	int lime_cairo_font_face_get_reference_count (value handle) {
		
		cairo_font_face_t *font_face = val_to_cairo_font_face_t (handle);
		if (font_face == NULL) return 0;
		return cairo_font_face_get_reference_count (font_face);
		
	}
	
	
	void lime_cairo_font_face_reference (value handle) {
		
		cairo_font_face_t *font_face = val_to_cairo_font_face_t (handle);
		if (font_face == NULL) return;
		cairo_font_face_reference (font_face);
		
	}
	
	
	int lime_cairo_font_face_status (value handle) {
		
		cairo_font_face_t *font_face = val_to_cairo_font_face_t (handle);
		if (font_face == NULL) return 0;
		return cairo_font_face_status (font_face);
		
	}
	
	
	value lime_cairo_font_options_create () {
		
		return cairo_font_options_t_to_value (cairo_font_options_create (), true);
		
	}
	
	
	void lime_cairo_font_options_destroy (value handle) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return;
		cairo_font_options_destroy (options);
		free_abstract (handle);
		
	}
	
	
	int lime_cairo_font_options_get_antialias (value handle) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return 0;
		return cairo_font_options_get_antialias (options);
		
	}
	
	
	int lime_cairo_font_options_get_hint_metrics (value handle) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return 0;
		return cairo_font_options_get_hint_metrics (options);
		
	}
	
	
	int lime_cairo_font_options_get_hint_style (value handle) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return 0;
		return cairo_font_options_get_hint_style (options);
		
	}
	
	
	int lime_cairo_font_options_get_subpixel_order (value handle) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return 0;
		return cairo_font_options_get_subpixel_order (options);
		
	}
	
	
	void lime_cairo_font_options_set_antialias (value handle, int v) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return;
		cairo_font_options_set_antialias (options, (cairo_antialias_t)v);
		
	}
	
	
	void lime_cairo_font_options_set_hint_metrics (value handle, int v) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return;
		cairo_font_options_set_hint_metrics (options, (cairo_hint_metrics_t)v);
		
	}
	
	
	void lime_cairo_font_options_set_hint_style (value handle, int v) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return;
		cairo_font_options_set_hint_style (options, (cairo_hint_style_t)v);
		
	}
	
	
	void lime_cairo_font_options_set_subpixel_order (value handle, int v) {
		
		cairo_font_options_t *options = val_to_cairo_font_options_t (handle);
		if (options == NULL) return;
		cairo_font_options_set_subpixel_order (options, (cairo_subpixel_order_t)v);
		
	}
	
	
	value lime_cairo_ft_font_face_create (value face, int flags) {
		
		#ifdef LIME_FREETYPE
		Font *font = val_to_Font (face);
		if (font == NULL) return alloc_null ();
		cairo_font_face_t* cairoFont = cairo_ft_font_face_create_for_ft_face ((FT_Face)font->face, flags);
		
		AutoGCRoot* fontReference = new AutoGCRoot (face);
		cairo_font_face_set_user_data (cairoFont, &userData, fontReference, gc_user_data);
		
		return cairo_font_face_t_to_value (cairoFont, true);
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_cairo_get_antialias (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_antialias (cairo);
		
	}
	
	
	value lime_cairo_get_current_point (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		
		double x, y;
		cairo_get_current_point (cairo, &x, &y);
		Vector2 vec2 = Vector2 (x, y);
		return vec2.Value ();
		
	}
	
	
	value lime_cairo_get_dash (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();

		int length = cairo_get_dash_count (cairo);
		
		double* dashes = new double[length];
		double offset;
		
		cairo_get_dash (cairo, dashes, &offset);
		
		value result = alloc_array (length);
		
		for (int i = 0; i < length; i++) {
			
			val_array_set_i (result, i, alloc_float (dashes[i]));
			
		}
		
		delete dashes;
		return result;
		
	}
	
	
	int lime_cairo_get_dash_count (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_dash_count (cairo);
		
	}
	
	
	int lime_cairo_get_fill_rule (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_fill_rule (cairo);
		
	}
	
	
	value lime_cairo_get_font_face (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		return cairo_font_face_t_to_value (cairo_get_font_face (cairo));
		
	}
	
	
	value lime_cairo_get_font_options (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		cairo_font_options_t *options = 0;
		cairo_get_font_options (cairo, options);
		return cairo_font_options_t_to_value (options);
		
	}
	
	
	value lime_cairo_get_group_target (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		return cairo_surface_t_to_value (cairo_get_group_target (cairo));
		
	}
	
	
	int lime_cairo_get_line_cap (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_line_cap (cairo);
		
	}
	
	
	int lime_cairo_get_line_join (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_line_join (cairo);
		
	}
	
	
	double lime_cairo_get_line_width (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_line_width (cairo);
		
	}
	
	
	value lime_cairo_get_matrix (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();

		cairo_matrix_t cm;
		cairo_get_matrix (cairo, &cm);
		Matrix3 mat3 = Matrix3 (cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0);
		return mat3.Value ();
		
	}
	
	
	double lime_cairo_get_miter_limit (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_miter_limit (cairo);
		
	}
	
	
	int lime_cairo_get_operator (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_operator (cairo);
		
	}
	
	
	int lime_cairo_get_reference_count (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_reference_count (cairo);
		
	}
	
	
	value lime_cairo_get_source (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		return cairo_pattern_t_to_value (cairo_get_source (cairo));
		
	}
	
	
	value lime_cairo_get_target (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		return cairo_surface_t_to_value (cairo_get_target (cairo));
		
	}
	
	
	double lime_cairo_get_tolerance (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_get_tolerance (cairo);
		
	}
	
	
	bool lime_cairo_has_current_point (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return false;
		return cairo_has_current_point (cairo);
		
	}
	
	
	void lime_cairo_identity_matrix (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_identity_matrix (cairo);
		
	}
	
	
	value lime_cairo_image_surface_create (int format, int width, int height) {
		
		return cairo_surface_t_to_value (cairo_image_surface_create ((cairo_format_t)format, width, height), true);
		
	}
	
	
	value lime_cairo_image_surface_create_for_data (double data, int format, int width, int height, int stride) {
		
		#ifndef LIME_NO_RAW_POINTER_ACESS
		return cairo_surface_t_to_value (cairo_image_surface_create_for_data ((unsigned char*)(intptr_t)data, (cairo_format_t)format, width, height, stride), true);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	double lime_cairo_image_surface_get_data (value handle) {
		
		#ifndef LIME_NO_RAW_POINTER_ACESS
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return 0;
		return (intptr_t)cairo_image_surface_get_data (surface);
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_cairo_image_surface_get_format (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return 0;
		return (int)cairo_image_surface_get_format (surface);
		
	}
	
	
	int lime_cairo_image_surface_get_height (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return 0;
		return cairo_image_surface_get_height (surface);
		
	}
	
	
	int lime_cairo_image_surface_get_stride (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return 0;
		return cairo_image_surface_get_stride (surface);
		
	}
	
	
	int lime_cairo_image_surface_get_width (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return 0;
		return cairo_image_surface_get_width (surface);
		
	}
	
	
	bool lime_cairo_in_clip (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return false;
		return cairo_in_clip (cairo, x, y);
		
	}
	
	
	bool lime_cairo_in_fill (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return false;
		return cairo_in_fill (cairo, x, y);
		
	}
	
	
	bool lime_cairo_in_stroke (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return false;
		return cairo_in_stroke (cairo, x, y);
		
	}
	
	
	void lime_cairo_line_to (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_line_to (cairo, x, y);
		
	}
	
	
	void lime_cairo_mask (value handle, value inPattern) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (inPattern);
		if (pattern == NULL) return;
		cairo_mask (cairo, pattern);
		
	}
	
	
	void lime_cairo_mask_surface (value handle, value inSurface, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_surface_t *surface = val_to_cairo_surface_t (inSurface);
		if (surface == NULL) return;
		cairo_mask_surface (cairo, surface, x, y);
		
	}
	
	
	void lime_cairo_move_to (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_move_to (cairo, x, y);
		
	}
	
	
	void lime_cairo_new_path (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_new_path (cairo);
		
	}
	
	
	void lime_cairo_paint (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_paint (cairo);
		
	}
	
	
	void lime_cairo_paint_with_alpha (value handle, double alpha) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_paint_with_alpha (cairo, alpha);
		
	}
	
	
	void lime_cairo_pattern_add_color_stop_rgb (value handle, double offset, double red, double green, double blue) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		cairo_pattern_add_color_stop_rgb (pattern, offset, red, green, blue);
		
	}
	
	
	void lime_cairo_pattern_add_color_stop_rgba (value handle, double offset, double red, double green, double blue, double alpha) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		cairo_pattern_add_color_stop_rgba (pattern, offset, red, green, blue, alpha);
		
	}
	
	
	value lime_cairo_pattern_create_for_surface (value inSurface) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (inSurface);
		if (surface == NULL) return alloc_null ();
		return cairo_pattern_t_to_value (cairo_pattern_create_for_surface (surface), true);
		
	}
	
	
	value lime_cairo_pattern_create_linear (double x0, double y0, double x1, double y1) {
		
		return cairo_pattern_t_to_value (cairo_pattern_create_linear (x0, y0, x1, y1), true);
		
	}
	
	
	value lime_cairo_pattern_create_radial (double cx0, double cy0, double radius0, double cx1, double cy1, double radius1) {
		
		return cairo_pattern_t_to_value (cairo_pattern_create_radial (cx0, cy0, radius0, cx1, cy1, radius1), true);
		
	}
	
	
	value lime_cairo_pattern_create_rgb (double r, double g, double b) {
		
		return cairo_pattern_t_to_value (cairo_pattern_create_rgb (r, g, b), true);
		
	}
	
	
	value lime_cairo_pattern_create_rgba (double r, double g, double b, double a) {
		
		return cairo_pattern_t_to_value (cairo_pattern_create_rgba (r, g, b, a), true);
		
	}
	
	
	void lime_cairo_pattern_destroy (value handle) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		cairo_pattern_destroy (pattern);
		free_abstract (handle);
		
	}
	
	
	int lime_cairo_pattern_get_color_stop_count (value handle) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return 0;
		
		int count;
		cairo_pattern_get_color_stop_count (pattern, &count);
		return count;
		
	}
	
	
	int lime_cairo_pattern_get_extend (value handle) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return 0;
		return cairo_pattern_get_extend (pattern);
		
	}
	
	
	int lime_cairo_pattern_get_filter (value handle) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return 0;
		return cairo_pattern_get_filter (pattern);
		
	}
	
	
	value lime_cairo_pattern_get_matrix (value handle) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return alloc_null ();

		cairo_matrix_t cm;
		cairo_pattern_get_matrix (pattern, &cm);
		Matrix3 mat3 = Matrix3 (cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0);
		return mat3.Value ();
		
	}
	
	
	void lime_cairo_pattern_set_extend (value handle, int extend) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		cairo_pattern_set_extend (pattern, (cairo_extend_t)extend);
		
	}
	
	
	void lime_cairo_pattern_set_filter (value handle, int filter) {
		
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		cairo_pattern_set_filter (pattern, (cairo_filter_t)filter);
		
	}
	
	
	void lime_cairo_pattern_set_matrix (value handle, value matrix) {

		cairo_pattern_t *pattern = val_to_cairo_pattern_t (handle);
		if (pattern == NULL) return;
		
		Matrix3 mat3 = Matrix3 (matrix);
		
		cairo_matrix_t cm;
		cairo_matrix_init (&cm, mat3.a, mat3.b, mat3.c, mat3.d, mat3.tx, mat3.ty);
		
		cairo_pattern_set_matrix (pattern, &cm);
		
	}
	
	
	value lime_cairo_pop_group (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return alloc_null ();
		return cairo_pattern_t_to_value (cairo_pop_group (cairo));
		
	}
	
	
	void lime_cairo_pop_group_to_source (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_pop_group_to_source (cairo);
		
	}
	
	
	void lime_cairo_push_group (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_push_group (cairo);
		
	}
	
	
	void lime_cairo_push_group_with_content (value handle, int content) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_push_group_with_content (cairo, (cairo_content_t)content);
		
	}
	
	
	void lime_cairo_rectangle (value handle, double x, double y, double width, double height) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_rectangle (cairo, x, y, width, height);
		
	}
	
	
	void lime_cairo_reference (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_reference (cairo);
		
	}
	
	
	void lime_cairo_rel_curve_to (value handle, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_rel_curve_to (cairo, dx1, dy1, dx2, dy2, dx3, dy3);
		
	}
	
	
	void lime_cairo_rel_line_to (value handle, double dx, double dy) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_rel_line_to (cairo, dx, dy);
		
	}
	
	
	void lime_cairo_rel_move_to (value handle, double dx, double dy) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_rel_move_to (cairo, dx, dy);
		
	}
	
	
	void lime_cairo_reset_clip (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_reset_clip (cairo);
		
	}
	
	
	void lime_cairo_restore (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_restore (cairo);
		
	}
	
	
	void lime_cairo_rotate (value handle, double amount) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_rotate (cairo, amount);
		
	}
	
	
	void lime_cairo_save (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_save (cairo);
		
	}
	
	
	void lime_cairo_scale (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_scale (cairo, x, y);
		
	}
	
	
	void lime_cairo_set_antialias (value handle, int cap) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_antialias (cairo, (cairo_antialias_t)cap);
		
	}
	
	
	void lime_cairo_set_dash (value handle, value dash) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		
		int length = val_array_size (dash);
		
		double* dashPattern = new double[length];
		
		for (int i = 0; i < length; i++) {
			
			dashPattern[i] = val_number (val_array_i (dash, i));
			
		}
		
		cairo_set_dash (cairo, dashPattern, length, 0);
		delete dashPattern;
		
	}
	
	
	void lime_cairo_set_fill_rule (value handle, int cap) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_fill_rule (cairo, (cairo_fill_rule_t)cap);
		
	}
	
	
	void lime_cairo_set_font_face (value handle, value inFace) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_font_face_t *face = val_to_cairo_font_face_t (inFace);
		if (face == NULL) return;
		cairo_set_font_face (cairo, face);
		
	}
	
	
	void lime_cairo_set_font_options (value handle, value inOptions) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_font_options_t *options = val_to_cairo_font_options_t (inOptions);
		if (options == NULL) return;
		cairo_set_font_options (cairo, options);
		
	}
	
	
	void lime_cairo_set_font_size (value handle, double size) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_font_size (cairo, size);
		
	}
	
	
	void lime_cairo_set_line_cap (value handle, int cap) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_line_cap (cairo, (cairo_line_cap_t)cap);
		
	}
	
	
	void lime_cairo_set_line_join (value handle, int join) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_line_join (cairo, (cairo_line_join_t)join);
		
	}
	
	
	void lime_cairo_set_line_width (value handle, double width) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_line_width (cairo, width);
		
	}
	
	
	void lime_cairo_set_matrix (value handle, value matrix) {

		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		
		Matrix3 mat3 = Matrix3 (matrix);
		
		cairo_matrix_t cm;
		cairo_matrix_init (&cm, mat3.a, mat3.b, mat3.c, mat3.d, mat3.tx, mat3.ty);
		
		cairo_set_matrix (cairo, &cm);
		
	}
	
	
	void lime_cairo_set_miter_limit (value handle, double miterLimit) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_miter_limit (cairo, miterLimit);
		
	}
	
	
	void lime_cairo_set_operator (value handle, int op) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_operator (cairo, (cairo_operator_t)op);
		
	}
	
	
	void lime_cairo_set_source (value handle, value inPattern) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_pattern_t *pattern = val_to_cairo_pattern_t (inPattern);
		if (pattern == NULL) return;
		cairo_set_source (cairo, pattern);
		
	}
	
	
	void lime_cairo_set_source_rgb (value handle, double r, double g, double b) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_source_rgb (cairo, r, g, b);
		
	}
	
	
	void lime_cairo_set_source_rgba (value handle, double r, double g, double b, double a) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_source_rgba (cairo, r, g, b, a);
		
	}
	
	
	void lime_cairo_set_source_surface (value handle, value inSurface, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_surface_t *surface = val_to_cairo_surface_t (inSurface);
		if (surface == NULL) return;
		cairo_set_source_surface (cairo, surface, x, y);
		
	}
	
	
	void lime_cairo_set_tolerance (value handle, double tolerance) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_set_tolerance (cairo, tolerance);
		
	}
	
	
	void lime_cairo_show_page (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_show_page (cairo);
		
	}
	
	
	void lime_cairo_show_text (value handle, HxString text) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_show_text (cairo, (char*)text.__s);
		
	}
	
	
	int lime_cairo_status (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return 0;
		return cairo_status (cairo);
		
	}
	
	
	void lime_cairo_stroke (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_stroke (cairo);
		
	}
	
	
	void lime_cairo_stroke_extents (value handle, double x1, double y1, double x2, double y2) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_stroke_extents (cairo, &x1, &y1, &x2, &y2);
		
	}
	
	
	void lime_cairo_stroke_preserve (value handle) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_stroke_preserve (cairo);
		
	}
	
	
	void lime_cairo_surface_destroy (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return;
		cairo_surface_destroy (surface);
		free_abstract (handle);
		
	}
	
	
	void lime_cairo_surface_flush (value handle) {
		
		cairo_surface_t *surface = val_to_cairo_surface_t (handle);
		if (surface == NULL) return;
		cairo_surface_flush (surface);
		
	}
	
	
	void lime_cairo_transform (value handle, value matrix) {

		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		
		Matrix3 mat3 = Matrix3 (matrix);
		
		cairo_matrix_t cm;
		cairo_matrix_init (&cm, mat3.a, mat3.b, mat3.c, mat3.d, mat3.tx, mat3.ty);
		
		cairo_transform (cairo, &cm);
		
	}
	
	
	void lime_cairo_translate (value handle, double x, double y) {
		
		cairo_t *cairo = val_to_cairo_t (handle);
		if (cairo == NULL) return;
		cairo_translate (cairo, x, y);
		
	}
	
	
	int lime_cairo_version () {
		
		return cairo_version ();
		
	}
	
	
	HxString lime_cairo_version_string () {
		
		const char* version = cairo_version_string ();
		return version ? HxString (version) : HxString (0, 0);
		
	}
	
	
	DEFINE_PRIME6v (lime_cairo_arc);
	DEFINE_PRIME6v (lime_cairo_arc_negative);
	DEFINE_PRIME1v (lime_cairo_clip);
	DEFINE_PRIME5v (lime_cairo_clip_extents);
	DEFINE_PRIME1v (lime_cairo_clip_preserve);
	DEFINE_PRIME1v (lime_cairo_close_path);
	DEFINE_PRIME1v (lime_cairo_copy_page);
	DEFINE_PRIME1 (lime_cairo_create);
	DEFINE_PRIME7v (lime_cairo_curve_to);
	DEFINE_PRIME1v (lime_cairo_destroy);
	DEFINE_PRIME1v (lime_cairo_fill);
	DEFINE_PRIME5v (lime_cairo_fill_extents);
	DEFINE_PRIME1v (lime_cairo_fill_preserve);
	DEFINE_PRIME2 (lime_cairo_ft_font_face_create);
	DEFINE_PRIME1 (lime_cairo_font_face_get_reference_count);
	DEFINE_PRIME1v (lime_cairo_font_face_reference);
	DEFINE_PRIME1 (lime_cairo_font_face_status);
	DEFINE_PRIME0 (lime_cairo_font_options_create);
	DEFINE_PRIME1v (lime_cairo_font_options_destroy);
	DEFINE_PRIME1 (lime_cairo_font_options_get_antialias);
	DEFINE_PRIME1 (lime_cairo_font_options_get_subpixel_order);
	DEFINE_PRIME1 (lime_cairo_font_options_get_hint_style);
	DEFINE_PRIME1 (lime_cairo_font_options_get_hint_metrics);
	DEFINE_PRIME2v (lime_cairo_font_options_set_antialias);
	DEFINE_PRIME2v (lime_cairo_font_options_set_subpixel_order);
	DEFINE_PRIME2v (lime_cairo_font_options_set_hint_style);
	DEFINE_PRIME2v (lime_cairo_font_options_set_hint_metrics);
	DEFINE_PRIME1 (lime_cairo_get_antialias);
	DEFINE_PRIME1 (lime_cairo_get_current_point);
	DEFINE_PRIME1 (lime_cairo_get_dash);
	DEFINE_PRIME1 (lime_cairo_get_dash_count);
	DEFINE_PRIME1 (lime_cairo_get_fill_rule);
	DEFINE_PRIME1 (lime_cairo_get_font_face);
	DEFINE_PRIME1 (lime_cairo_get_font_options);
	DEFINE_PRIME1 (lime_cairo_get_group_target);
	DEFINE_PRIME1 (lime_cairo_get_line_cap);
	DEFINE_PRIME1 (lime_cairo_get_line_join);
	DEFINE_PRIME1 (lime_cairo_get_line_width);
	DEFINE_PRIME1 (lime_cairo_get_matrix);
	DEFINE_PRIME1 (lime_cairo_get_miter_limit);
	DEFINE_PRIME1 (lime_cairo_get_operator);
	DEFINE_PRIME1 (lime_cairo_get_reference_count);
	DEFINE_PRIME1 (lime_cairo_get_source);
	DEFINE_PRIME1 (lime_cairo_get_target);
	DEFINE_PRIME1 (lime_cairo_get_tolerance);
	DEFINE_PRIME1 (lime_cairo_has_current_point);
	DEFINE_PRIME1v (lime_cairo_identity_matrix);
	DEFINE_PRIME3v (lime_cairo_image_surface_create);
	DEFINE_PRIME5 (lime_cairo_image_surface_create_for_data);
	DEFINE_PRIME1 (lime_cairo_image_surface_get_data);
	DEFINE_PRIME1 (lime_cairo_image_surface_get_format);
	DEFINE_PRIME1 (lime_cairo_image_surface_get_height);
	DEFINE_PRIME1 (lime_cairo_image_surface_get_stride);
	DEFINE_PRIME1 (lime_cairo_image_surface_get_width);
	DEFINE_PRIME3 (lime_cairo_in_clip);
	DEFINE_PRIME3 (lime_cairo_in_fill);
	DEFINE_PRIME3 (lime_cairo_in_stroke);
	DEFINE_PRIME3v (lime_cairo_line_to);
	DEFINE_PRIME2v (lime_cairo_mask);
	DEFINE_PRIME4v (lime_cairo_mask_surface);
	DEFINE_PRIME3v (lime_cairo_move_to);
	DEFINE_PRIME1v (lime_cairo_new_path);
	DEFINE_PRIME1v (lime_cairo_paint);
	DEFINE_PRIME2v (lime_cairo_paint_with_alpha);
	DEFINE_PRIME5v (lime_cairo_pattern_add_color_stop_rgb);
	DEFINE_PRIME6v (lime_cairo_pattern_add_color_stop_rgba);
	DEFINE_PRIME1 (lime_cairo_pattern_create_for_surface);
	DEFINE_PRIME4 (lime_cairo_pattern_create_linear);
	DEFINE_PRIME6 (lime_cairo_pattern_create_radial);
	DEFINE_PRIME3 (lime_cairo_pattern_create_rgb);
	DEFINE_PRIME4 (lime_cairo_pattern_create_rgba);
	DEFINE_PRIME1v (lime_cairo_pattern_destroy);
	DEFINE_PRIME1 (lime_cairo_pattern_get_color_stop_count);
	DEFINE_PRIME1 (lime_cairo_pattern_get_extend);
	DEFINE_PRIME1 (lime_cairo_pattern_get_filter);
	DEFINE_PRIME1 (lime_cairo_pattern_get_matrix);
	DEFINE_PRIME2v (lime_cairo_pattern_set_extend);
	DEFINE_PRIME2v (lime_cairo_pattern_set_filter);
	DEFINE_PRIME2v (lime_cairo_pattern_set_matrix);
	DEFINE_PRIME1 (lime_cairo_pop_group);
	DEFINE_PRIME1v (lime_cairo_pop_group_to_source);
	DEFINE_PRIME1v (lime_cairo_push_group);
	DEFINE_PRIME2v (lime_cairo_push_group_with_content);
	DEFINE_PRIME5v (lime_cairo_rectangle);
	DEFINE_PRIME1v (lime_cairo_reference);
	DEFINE_PRIME7v (lime_cairo_rel_curve_to);
	DEFINE_PRIME3v (lime_cairo_rel_line_to);
	DEFINE_PRIME3v (lime_cairo_rel_move_to);
	DEFINE_PRIME1v (lime_cairo_reset_clip);
	DEFINE_PRIME1v (lime_cairo_restore);
	DEFINE_PRIME2v (lime_cairo_rotate);
	DEFINE_PRIME1v (lime_cairo_save);
	DEFINE_PRIME3v (lime_cairo_scale);
	DEFINE_PRIME2v (lime_cairo_set_antialias);
	DEFINE_PRIME2v (lime_cairo_set_dash);
	DEFINE_PRIME2v (lime_cairo_set_fill_rule);
	DEFINE_PRIME2v (lime_cairo_set_font_face);
	DEFINE_PRIME2v (lime_cairo_set_font_size);
	DEFINE_PRIME2v (lime_cairo_set_font_options);
	DEFINE_PRIME2v (lime_cairo_set_line_cap);
	DEFINE_PRIME2v (lime_cairo_set_line_join);
	DEFINE_PRIME2v (lime_cairo_set_line_width);
	DEFINE_PRIME2v (lime_cairo_set_matrix);
	DEFINE_PRIME2v (lime_cairo_set_miter_limit);
	DEFINE_PRIME2v (lime_cairo_set_operator);
	DEFINE_PRIME2v (lime_cairo_set_source);
	DEFINE_PRIME4v (lime_cairo_set_source_rgb);
	DEFINE_PRIME5v (lime_cairo_set_source_rgba);
	DEFINE_PRIME4v (lime_cairo_set_source_surface);
	DEFINE_PRIME2v (lime_cairo_set_tolerance);
	DEFINE_PRIME1v (lime_cairo_show_page);
	DEFINE_PRIME2v (lime_cairo_show_text);
	DEFINE_PRIME1 (lime_cairo_status);
	DEFINE_PRIME1v (lime_cairo_stroke);
	DEFINE_PRIME5v (lime_cairo_stroke_extents);
	DEFINE_PRIME1v (lime_cairo_stroke_preserve);
	DEFINE_PRIME1v (lime_cairo_surface_destroy);
	DEFINE_PRIME1v (lime_cairo_surface_flush);
	DEFINE_PRIME2v (lime_cairo_transform);
	DEFINE_PRIME3v (lime_cairo_translate);
	DEFINE_PRIME0 (lime_cairo_version);
	DEFINE_PRIME0 (lime_cairo_version_string);
	
	
}


extern "C" int lime_cairo_register_prims () {
	
	return 0;
	
}