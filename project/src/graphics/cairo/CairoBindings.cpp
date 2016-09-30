#include <cairo.h>
#include <cairo-ft.h>
#include <graphics/ImageBuffer.h>
#include <math/Matrix3.h>
#include <math/Vector2.h>
//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <text/Font.h>
#include <utils/HxVector.h>

#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {
	
	
	static int id_index;
	static int id_x;
	static int id_y;
	static bool init = false;
	cairo_user_data_key_t userData;
	
	
	void gc_bytes (void* inData) {
		
		Bytes* data = (Bytes*)inData;
		delete data;
		
	}
	
	
	void gc_user_data (void* data) {
		
		AutoGCRoot* reference = (AutoGCRoot*)data;
		delete reference;
		
	}
	
	
	cairo_font_face_t* cairo_ft_font_face_create_wrap (value face, int flags) {
		
		#ifdef LIME_FREETYPE
		Font* font = val_to_Font (face);
		cairo_font_face_t* cairoFont = cairo_ft_font_face_create_for_ft_face ((FT_Face)font->face, flags);
		
		AutoGCRoot* fontReference = new AutoGCRoot (face);
		cairo_font_face_set_user_data (cairoFont, &userData, fontReference, gc_user_data);
		
		return cairoFont;
		#else
		return 0;
		#endif
		
	}
	
	
	value cairo_get_current_point_wrap (cairo_t* cairo) {
		
		double x, y;
		cairo_get_current_point (cairo, &x, &y);
		Vector2 vec2 = Vector2 (x, y);
		return vec2.Value ();
		
	}
	
	
	value cairo_get_dash_wrap (cairo_t* cairo) {
		
		int length = cairo_get_dash_count (cairo);
		
		double* dashes = new double[length];
		double offset;
		
		cairo_get_dash (cairo, dashes, &offset);
		
		value result = alloc_array (length);
		
		for (int i = 0; i < length; i++) {
			
			val_array_set_i (result, i, alloc_float (dashes[i]));
			
		}
		
		delete[] dashes;
		return result;
		
	}
	
	
	cairo_font_face_t* cairo_get_font_face_wrap (cairo_t* cairo) {
		
		cairo_font_face_t* face = cairo_get_font_face (cairo);
		cairo_font_face_reference (face);
		return face;
		
	}
	
	
	cairo_font_options_t* cairo_get_font_options_wrap (cairo_t* cairo) {
		
		cairo_font_options_t *options = cairo_font_options_create ();
		cairo_get_font_options (cairo, options);
		return options;
		
	}
	
	
	value cairo_get_matrix_wrap (cairo_t* cairo) {
		
		cairo_matrix_t cm;
		cairo_get_matrix (cairo, &cm);
		Matrix3 mat3 = Matrix3 (cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0);
		return mat3.Value ();
		
	}
	
	
	cairo_pattern_t* cairo_get_source_wrap (cairo_t* cairo) {
		
		cairo_pattern_t* pattern = cairo_get_source (cairo);
		cairo_pattern_reference (pattern);
		return pattern;
		
	}
	
	
	cairo_surface_t* cairo_image_surface_create_for_bytes (value inData, cairo_format_t format, int width, int height, int stride) {
		
		Bytes *data = new Bytes ();
		
		if (!data->Set (inData)) {
			
			delete data;
			return NULL;
			
		}
		
		data->Pin ();
		cairo_surface_t *surface = cairo_image_surface_create_for_data (data->Data (), format, width, height, stride);
		cairo_surface_set_user_data (surface, &userData, data, gc_bytes);
		
		return surface;
		
	}
	
	
	int cairo_pattern_get_color_stop_count_wrap (cairo_pattern_t* pattern) {
		
		int count;
		cairo_pattern_get_color_stop_count (pattern, &count);
		return count;
		
	}
	
	
	value cairo_pattern_get_matrix_wrap (cairo_pattern_t* pattern) {
		
		cairo_matrix_t cm;
		cairo_pattern_get_matrix (pattern, &cm);
		Matrix3 mat3 = Matrix3 (cm.xx, cm.yx, cm.xy, cm.yy, cm.x0, cm.y0);
		return mat3.Value ();
		
	}
	
	
	void cairo_set_dash_wrap (cairo_t* cairo, const HxVector<double>& dashPattern) {
		
		cairo_set_dash (cairo, dashPattern.Data (), dashPattern.Length (), 0);
		
	}
	
	
	void cairo_set_font_size_wrap (cairo_t* cairo, double size) {
		
		cairo_font_face_t* face = cairo_get_font_face (cairo);
		
		if (face) {
			
			cairo_font_type_t type = cairo_font_face_get_type (face);
			
			if (type == CAIRO_FONT_TYPE_FT) {
				
				AutoGCRoot* fontReference = (AutoGCRoot*)cairo_font_face_get_user_data (face, &userData);
				
				if (fontReference) {
					
					// TODO
					Font* font = (Font*)val_data (fontReference->get ());
					font->SetSize (size);
					
				}
				
			}
			
		}
		
		cairo_set_font_size (cairo, size);
		
	}
	
	void cairo_show_glyphs_wrap (cairo_t* cairo, value glyphs) {
		
		if (!init) {
			
			id_index = val_id ("index");
			id_x = val_id ("x");
			id_y = val_id ("y");
			
		}
		
		int length = val_array_size (glyphs);
		cairo_glyph_t* _glyphs = cairo_glyph_allocate (length);
		
		value glyph;
		
		for (int i = 0; i < length; i++) {
			
			glyph = val_array_i (glyphs, i);
			_glyphs[i].index = val_int (val_field (glyph, id_index));
			_glyphs[i].x = val_number (val_field (glyph, id_x));
			_glyphs[i].y = val_number (val_field (glyph, id_y));
			
		}
		
		cairo_show_glyphs (cairo, _glyphs, length);
		cairo_glyph_free (_glyphs);
		
	}
	
	
	void cairo_set_matrix_wrap (cairo_t* cairo, double a, double b, double c, double d, double tx, double ty) {
		
		cairo_matrix_t cm;
		cairo_matrix_init (&cm, a, b, c, d, tx, ty);
		
		cairo_set_matrix (cairo, &cm);
		
	}
	
	
	void gc_cairo (value handle) {
		
		cairo_t* cairo = (cairo_t*)val_data (handle);
		cairo_destroy (cairo);
		free_abstract (handle);
		
	}
	
	
	void gc_cairo_font_face (value handle) {
		
		cairo_font_face_t* face = (cairo_font_face_t*)val_data (handle);
		cairo_font_face_destroy (face);
		free_abstract (handle);
		
	}
	
	
	void gc_cairo_font_options (value handle) {
		
		cairo_font_options_t* options = (cairo_font_options_t*)val_data (handle);
		cairo_font_options_destroy (options);
		free_abstract (handle);
		
	}
	
	
	void gc_cairo_pattern (value handle) {
		
		cairo_pattern_t* pattern = (cairo_pattern_t*)val_data (handle);
		cairo_pattern_destroy (pattern);
		free_abstract (handle);
		
	}
	
	
	void gc_cairo_surface (value handle) {
			
		cairo_surface_t* surface = (cairo_surface_t*)val_data (handle);
		cairo_surface_destroy (surface);
		free_abstract (handle);
		
	}
	
	
	value cairo_t_to_val (cairo_t *inInstance) {
		
		return CFFIPointer (inInstance, gc_cairo, Kinds::Get ()->cairo_t);
		
	}
	
	
	cairo_t* val_to_cairo_t (value inHandle) {
		
		return lime_abstract_to_pointer<cairo_t> (inHandle, Kinds::Get ()->cairo_t);
		
	}
	
	
	value cairo_font_face_t_to_val (cairo_font_face_t* inInstance) {
		
		return CFFIPointer (inInstance, gc_cairo_font_face, Kinds::Get ()->cairo_font_face_t);
		
	}
	
	
	cairo_font_face_t* val_to_cairo_font_face_t (value inHandle) {
		
		return lime_abstract_to_pointer<cairo_font_face_t> (inHandle, Kinds::Get ()->cairo_font_face_t);
		
	}
	
	
	value cairo_font_options_t_to_val (cairo_font_options_t* inInstance) {
		
		return CFFIPointer (inInstance, gc_cairo_font_options, Kinds::Get ()->cairo_font_options_t);
		
	}
	
	
	cairo_font_options_t* val_to_cairo_font_options_t (value inHandle) {
		
		return lime_abstract_to_pointer<cairo_font_options_t> (inHandle, Kinds::Get ()->cairo_font_options_t);
		
	}
	
	value cairo_pattern_t_to_val (cairo_pattern_t* inInstance) {
		
		return CFFIPointer (inInstance, gc_cairo_pattern, Kinds::Get ()->cairo_pattern_t);
		
	}
	
	
	cairo_pattern_t* val_to_cairo_pattern_t (value inHandle) {
		
		return lime_abstract_to_pointer<cairo_pattern_t> (inHandle, Kinds::Get ()->cairo_pattern_t);
		
	}
	
	
	value cairo_surface_t_to_val (cairo_surface_t* inInstance) {
		
		return CFFIPointer (inInstance, gc_cairo_surface, Kinds::Get ()->cairo_surface_t);
		
	}
	
	
	cairo_surface_t* val_to_cairo_surface_t (value inHandle) {
		
		return lime_abstract_to_pointer<cairo_surface_t> (inHandle, Kinds::Get ()->cairo_surface_t);
		
	}
	
	
	cairo_matrix_t val_to_cairo_matrix_t (value inHandle) {
		
		Matrix3 mat3 = Matrix3 (inHandle);
		
		cairo_matrix_t cm;
		cairo_matrix_init (&cm, mat3.a, mat3.b, mat3.c, mat3.d, mat3.tx, mat3.ty);
		return cm;
		
	}
	
	
}


extern "C" int lime_cairo_register_prims () {
	
	return 0;
	
}