#ifndef LIME_GRAPHICS_CAIRO_CAIRO_TYPES_H
#define LIME_GRAPHICS_CAIRO_CAIRO_TYPES_H

#include <cairo.h>
#include <graphics/ImageBuffer.h>
#include <hx/CFFI.h>
#include <text/Font.h>
#include <utils/HxVector.h>

namespace lime {
	
	value cairo_t_to_val (cairo_t* inInstance);
	
	cairo_t* val_to_cairo_t (value inHandle);
	
	value cairo_font_face_t_to_val (cairo_font_face_t* inInstance);
	
	cairo_font_face_t* val_to_cairo_font_face_t (value inHandle);
	
	value cairo_font_options_t_to_val (cairo_font_options_t* inInstance);
	
	cairo_font_options_t* val_to_cairo_font_options_t (value inHandle);
	
	value cairo_pattern_t_to_val (cairo_pattern_t* inInstance);
	
	cairo_pattern_t* val_to_cairo_pattern_t (value inHandle);
	
	value cairo_surface_t_to_val (cairo_surface_t* inInstance);
	
	cairo_surface_t* val_to_cairo_surface_t (value inHandle);
	
	cairo_matrix_t val_to_cairo_matrix_t (value inHandle);
	
	cairo_font_face_t* cairo_ft_font_face_create_wrap (value face, int flags);
	
	value cairo_get_current_point_wrap (cairo_t* cairo);
	
	value cairo_get_dash_wrap (cairo_t* cairo);
	
	cairo_font_face_t* cairo_get_font_face_wrap (cairo_t* cairo);
	
	cairo_font_options_t* cairo_get_font_options_wrap (cairo_t* cairo);
	
	value cairo_get_matrix_wrap (cairo_t* cairo);
	
	cairo_pattern_t* cairo_get_source_wrap (cairo_t* cairo);
	
	cairo_surface_t* cairo_image_surface_create_for_bytes (value inData, cairo_format_t format, int width, int height, int stride);
	
	cairo_surface_t* cairo_image_surface_create_for_image (ImageBuffer* image, cairo_format_t format, int width, int height, int stride);
	
	int cairo_pattern_get_color_stop_count_wrap (cairo_pattern_t* pattern);
	
	value cairo_pattern_get_matrix_wrap (cairo_pattern_t* pattern);
	
	void cairo_set_dash_wrap (cairo_t* cairo, const HxVector<double>& dashPattern);
	
	void cairo_set_font_size_wrap (cairo_t* cairo, double size);
	
	void cairo_set_matrix_wrap (cairo_t* cairo, double a, double b, double c, double d, double tx, double ty);
	
	void cairo_show_glyphs_wrap (cairo_t* cairo, value glyphs);
	
}

#endif