#include <text/Font.h>
#include <graphics/ImageBuffer.h>
#include <system/System.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>
#include <utils/StringId.h>

#include <algorithm>
#include <list>
#include <memory>
#include <vector>

#ifdef LIME_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#endif


// from http://stackoverflow.com/questions/2948308/how-do-i-read-utf-8-characters-via-a-pointer
#define IS_IN_RANGE(c, f, l) (((c) >= (f)) && ((c) <= (l)))


unsigned long readNextChar (const char*& p)
{
	 // TODO: since UTF-8 is a variable-length
	 // encoding, you should pass in the input
	 // buffer's actual byte length so that you
	 // can determine if a malformed UTF-8
	 // sequence would exceed the end of the buffer...

	 unsigned char c1, c2, *ptr = (unsigned char*) p;
	 unsigned long uc = 0;
	 int seqlen;

	 c1 = ptr[0];

	 if ((c1 & 0x80) == 0) {

		  uc = (unsigned long) (c1 & 0x7F);
		  seqlen = 1;

	 } else if ((c1 & 0xE0) == 0xC0) {

		  uc = (unsigned long) (c1 & 0x1F);
		  seqlen = 2;

	 } else if ((c1 & 0xF0) == 0xE0) {

		  uc = (unsigned long) (c1 & 0x0F);
		  seqlen = 3;

	 } else if ((c1 & 0xF8) == 0xF0) {

		  uc = (unsigned long) (c1 & 0x07);
		  seqlen = 4;

	 } else {

		  // malformed data, do something !!!
		  return (unsigned long) -1;

	 }

	 for (int i = 1; i < seqlen; ++i) {

		  c1 = ptr[i];

		  if ((c1 & 0xC0) != 0x80) {

				// malformed data, do something !!!
				return (unsigned long) -1;

		  }

	 }

	 switch (seqlen) {
		  case 2:
				c1 = ptr[0];

				if (!IS_IN_RANGE(c1, 0xC2, 0xDF)) {

					 // malformed data, do something !!!
					 return (unsigned long) -1;

				}

				break;
		  case 3:
				c1 = ptr[0];
				c2 = ptr[1];

				if (((c1 == 0xE0) && !IS_IN_RANGE(c2, 0xA0, 0xBF)) ||
					 ((c1 == 0xED) && !IS_IN_RANGE(c2, 0x80, 0x9F)) ||
					 (!IS_IN_RANGE(c1, 0xE1, 0xEC) && !IS_IN_RANGE(c1, 0xEE, 0xEF))) {

					 // malformed data, do something !!!
					 return (unsigned long) -1;

				}

				break;
		  case 4:
				c1 = ptr[0];
				c2 = ptr[1];

				if (((c1 == 0xF0) && !IS_IN_RANGE(c2, 0x90, 0xBF)) ||
					 ((c1 == 0xF4) && !IS_IN_RANGE(c2, 0x80, 0x8F)) ||
					 !IS_IN_RANGE(c1, 0xF1, 0xF3)) {

					 // malformed data, do something !!!
					 return (unsigned long) -1;

				}

				break;
	 }

	 for (int i = 1; i < seqlen; ++i) {

		  uc = ((uc << 6) | (unsigned long)(ptr[i] & 0x3F));

	 }

	 p += seqlen;
	 return uc;
}


namespace {
	
	
	enum {
		
		PT_MOVE = 1,
		PT_LINE = 2,
		PT_CURVE = 3,
		PT_CUBIC = 4
		
	};
	
	
	struct point {
		
		int x, y;
		unsigned char type;
		
		point () { }
		point (int x, int y, unsigned char type) : x (x), y (y), type (type) { }
		
	};
	
	
	struct glyph {
		
		FT_ULong char_code;
		FT_Vector advance;
		FT_Glyph_Metrics metrics;
		int index, x, y;
		std::vector<int> pts;
		
		glyph () : x (0), y (0) { }
		
	};
	
	
	struct kerning {
		
		int l_glyph, r_glyph;
		int x, y;
		
		kerning () { }
		kerning (int l, int r, int x, int y) : l_glyph (l), r_glyph (r), x (x), y (y) { }
		
	};
	
	
	struct glyph_sort_predicate {
		
		bool operator () (const glyph* g1, const glyph* g2) const {
			
			return g1->char_code < g2->char_code;
			
		}
		
	};
	
	
	typedef const FT_Vector *FVecPtr;
	
	
	int outline_move_to (FVecPtr to, void *user) {
		
		glyph *g = static_cast<glyph*> (user);
		
		g->pts.push_back (PT_MOVE);
		g->pts.push_back (to->x);
		g->pts.push_back (to->y);
		
		g->x = to->x;
		g->y = to->y;
		
		return 0;
		
	}
	
	
	int outline_line_to (FVecPtr to, void *user) {
		
		glyph *g = static_cast<glyph*> (user);
		
		g->pts.push_back (PT_LINE);
		g->pts.push_back (to->x - g->x);
		g->pts.push_back (to->y - g->y);
		
		g->x = to->x;
		g->y = to->y;
		
		return 0;
		
	}
	
	
	int outline_conic_to (FVecPtr ctl, FVecPtr to, void *user) {
		
		glyph *g = static_cast<glyph*> (user);
		
		g->pts.push_back (PT_CURVE);
		g->pts.push_back (ctl->x - g->x);
		g->pts.push_back (ctl->y - g->y);
		g->pts.push_back (to->x - ctl->x);
		g->pts.push_back (to->y - ctl->y);
		
		g->x = to->x;
		g->y = to->y;
		
		return 0;
		
	}
	
	
	int outline_cubic_to (FVecPtr ctl1, FVecPtr ctl2, FVecPtr to, void *user) {
		
		glyph *g = static_cast<glyph*> (user);
		
		g->pts.push_back (PT_CUBIC);
		g->pts.push_back (ctl1->x - g->x);
		g->pts.push_back (ctl1->y - g->y);
		g->pts.push_back (ctl2->x - ctl1->x);
		g->pts.push_back (ctl2->y - ctl1->y);
		g->pts.push_back (to->x - ctl2->x);
		g->pts.push_back (to->y - ctl2->y);
		
		g->x = to->x;
		g->y = to->y;
		
		return 0;
		
	}
	
	
}


namespace lime {
	
	
	Font::Font (Resource *resource, int faceIndex) {
		
		this->library = 0;
		this->face = 0;
		this->faceMemoryPin = 0;
		
		if (resource) {
			
			int error;
			FT_Library library;
			
			error = FT_Init_FreeType (&library);
			
			if (error) {
				
				printf ("Could not initialize FreeType\n");
				
			} else {
				
				FT_Face face;
				FILE_HANDLE *file = NULL;
				
				if (resource->path) {
					
					file = lime::fopen (resource->path, "rb");
					
					if (!file) {
						
						FT_Done_FreeType (library);
						return;
						
					}
					
					if (file->isFile ()) {
						
						error = FT_New_Face (library, resource->path, faceIndex, &face);
						
					} else {
						
						Bytes faceMemory;
						int status = faceMemory.ReadFile (file);
						lime::fclose (file);
						file = 0;
						
						if (!status) {
							
							FT_Done_FreeType (library);
							return;
							
						}

						error = FT_New_Memory_Face (library, faceMemory.Data (), faceMemory.Length (), faceIndex, &face);
						this->faceMemoryPin = faceMemory.Pin ();
						
					}
					
				} else {
					
					error = FT_New_Memory_Face (library, resource->data->Data (), resource->data->Length (), faceIndex, &face);
					this->faceMemoryPin = resource->data->Pin ();
					
				}
				
				if (file) {
					
					lime::fclose (file);
					file = 0;
					
				}
				
				if (!error) {
					
					this->library = library;
					this->face = face;
					
					/* Set charmap
					 *
					 * See http://www.microsoft.com/typography/otspec/name.htm for a list of
					 * some possible platform-encoding pairs.  We're interested in 0-3 aka 3-1
					 * - UCS-2.  Otherwise, fail. If a font has some unicode map, but lacks
					 * UCS-2 - it is a broken or irrelevant font. What exactly Freetype will
					 * select on face load (it promises most wide unicode, and if that will be
					 * slower that UCS-2 - left as an excercise to check.
					 */
					for (int i = 0; i < ((FT_Face)face)->num_charmaps; i++) {
						
						FT_UShort pid = ((FT_Face)face)->charmaps[i]->platform_id;
						FT_UShort eid = ((FT_Face)face)->charmaps[i]->encoding_id;
						
						if (((pid == 0) && (eid == 3)) || ((pid == 3) && (eid == 1))) {
							
							FT_Set_Charmap ((FT_Face)face, ((FT_Face)face)->charmaps[i]);
							
						}
						
					}
					
				}
				
			}
			
		}
		
	}
	
	
	Font::~Font () {
		
		if (library) {
			
			FT_Done_FreeType ((FT_Library)library);
			
		}
		
		if (faceMemoryPin) {
			
			Bytes::Unpin (faceMemoryPin);
			
		}
		
	}
	
	
	value Font::Decompose (int em) {
		
		int result, i, j;
		
		FT_Set_Char_Size ((FT_Face)face, em, em, 72, 72);
		FT_Set_Transform ((FT_Face)face, 0, NULL);

		std::vector<glyph*> glyphs;
		
		FT_Outline_Funcs ofn =
		{
			outline_move_to,
			outline_line_to,
			outline_conic_to,
			outline_cubic_to,
			0, // shift
			0  // delta
		};
		
		// Import every character in face
		FT_ULong char_code;
		FT_UInt glyph_index;
		
		char_code = FT_Get_First_Char ((FT_Face)face, &glyph_index);
		
		while (glyph_index != 0) {
			
			if (FT_Load_Glyph ((FT_Face)face, glyph_index, FT_LOAD_NO_BITMAP | FT_LOAD_DEFAULT) == 0) {
				
				glyph *g = new glyph;
				result = FT_Outline_Decompose (&((FT_Face)face)->glyph->outline, &ofn, g);
				
				if (result == 0) {
					
					g->index = glyph_index;
					g->char_code = char_code;
					g->metrics = ((FT_Face)face)->glyph->metrics;
					glyphs.push_back (g);
					
				} else {
					
					delete g;
					
				}
				
			}
			
			char_code = FT_Get_Next_Char ((FT_Face)face, char_code, &glyph_index);
			
		}
		
		// Ascending sort by character codes
		std::sort (glyphs.begin (), glyphs.end (), glyph_sort_predicate ());
		
		std::vector<kerning>  kern;
		if (FT_HAS_KERNING (((FT_Face)face))) {
			
			int n = glyphs.size ();
			FT_Vector v;
			
			for (i = 0; i < n; i++) {
				
				int  l_glyph = glyphs[i]->index;
				
				for (j = 0; j < n; j++) {
					
					int r_glyph = glyphs[j]->index;
					
					FT_Get_Kerning ((FT_Face)face, l_glyph, r_glyph, FT_KERNING_DEFAULT, &v);
					
					if (v.x != 0 || v.y != 0) {
						
						kern.push_back (kerning (i, j, v.x, v.y));
						
					}
					
				}
				
			}
			
		}
		
		int num_glyphs = glyphs.size ();
		
		std::wstring family_name = GetFamilyName ();
		
		value ret = alloc_empty_object ();
		alloc_field (ret, val_id ("has_kerning"), alloc_bool (FT_HAS_KERNING (((FT_Face)face))));
		alloc_field (ret, val_id ("is_fixed_width"), alloc_bool (FT_IS_FIXED_WIDTH (((FT_Face)face))));
		alloc_field (ret, val_id ("has_glyph_names"), alloc_bool (FT_HAS_GLYPH_NAMES (((FT_Face)face))));
		alloc_field (ret, val_id ("is_italic"), alloc_bool (((FT_Face)face)->style_flags & FT_STYLE_FLAG_ITALIC));
		alloc_field (ret, val_id ("is_bold"), alloc_bool (((FT_Face)face)->style_flags & FT_STYLE_FLAG_BOLD));
		alloc_field (ret, val_id ("num_glyphs"), alloc_int (num_glyphs));
		alloc_field (ret, val_id ("family_name"), family_name.empty () ? alloc_string (((FT_Face)face)->family_name) : alloc_wstring (family_name.c_str ()));
		alloc_field (ret, val_id ("style_name"), alloc_string (((FT_Face)face)->style_name));
		alloc_field (ret, val_id ("em_size"), alloc_int (((FT_Face)face)->units_per_EM));
		alloc_field (ret, val_id ("ascend"), alloc_int (((FT_Face)face)->ascender));
		alloc_field (ret, val_id ("descend"), alloc_int (((FT_Face)face)->descender));
		alloc_field (ret, val_id ("height"), alloc_int (((FT_Face)face)->height));
		
		// 'glyphs' field
		value neko_glyphs = alloc_array (num_glyphs);
		for (i = 0; i < glyphs.size (); i++) {
			
			glyph *g = glyphs[i];
			int num_points = g->pts.size ();
			
			value points = alloc_array (num_points);
			
			for (j = 0; j < num_points; j++) {
				
				val_array_set_i (points, j, alloc_int (g->pts[j]));
				
			}
			
			value item = alloc_empty_object ();
			val_array_set_i (neko_glyphs, i, item);
			alloc_field (item, val_id ("char_code"), alloc_int (g->char_code));
			alloc_field (item, val_id ("advance"), alloc_int (g->metrics.horiAdvance));
			alloc_field (item, val_id ("min_x"), alloc_int (g->metrics.horiBearingX));
			alloc_field (item, val_id ("max_x"), alloc_int (g->metrics.horiBearingX + g->metrics.width));
			alloc_field (item, val_id ("min_y"), alloc_int (g->metrics.horiBearingY - g->metrics.height));
			alloc_field (item, val_id ("max_y"), alloc_int (g->metrics.horiBearingY));
			alloc_field (item, val_id ("points"), points);
			
			delete g;
			
		}
		
		alloc_field (ret, val_id ("glyphs"), neko_glyphs);
		
		// 'kerning' field
		if (FT_HAS_KERNING (((FT_Face)face))) {
			
			value neko_kerning = alloc_array (kern.size ());
			
			for (i = 0; i < kern.size (); i++) {
				
				kerning *k = &kern[i];
				
				value item = alloc_empty_object ();
				val_array_set_i (neko_kerning,i,item);
				alloc_field (item, val_id ("left_glyph"), alloc_int (k->l_glyph));
				alloc_field (item, val_id ("right_glyph"), alloc_int (k->r_glyph));
				alloc_field (item, val_id ("x"), alloc_int (k->x));
				alloc_field (item, val_id ("y"), alloc_int (k->y));
				
			}
			
			alloc_field (ret, val_id ("kerning"), neko_kerning);
			
		} else {
			
			alloc_field (ret, val_id ("kerning"), alloc_null ());
			
		}
		
		return ret;
		
	}
	
	
	int Font::GetAscender () {
		
		return ((FT_Face)face)->ascender;
		
	}
	
	
	int Font::GetDescender () {
		
		return ((FT_Face)face)->descender;
		
	}
	
	
	std::wstring Font::GetFamilyName () {
		
		#ifdef LIME_FREETYPE
		
		std::unique_ptr<wchar_t> stringPtr;
		wchar_t* family_name = 0;
		FT_SfntName sfnt_name;
		FT_UInt num_sfnt_names, sfnt_name_index;
		size_t len, i;
		
		if (FT_IS_SFNT (((FT_Face)face))) {
			
			num_sfnt_names = FT_Get_Sfnt_Name_Count ((FT_Face)face);
			sfnt_name_index = 0;
			
			while (sfnt_name_index < num_sfnt_names) {
				
				if (!FT_Get_Sfnt_Name ((FT_Face)face, sfnt_name_index++, (FT_SfntName *)&sfnt_name) && sfnt_name.name_id == TT_NAME_ID_FULL_NAME) {
					
					if (sfnt_name.platform_id == TT_PLATFORM_MACINTOSH) {
						
						len = sfnt_name.string_len;
						stringPtr.reset (new wchar_t[len + 1]);
						family_name = stringPtr.get ();
						mbstowcs (&family_name[0], &reinterpret_cast<const char*>(sfnt_name.string)[0], len);
						family_name[len] = L'\0';
						return std::wstring (family_name);
						
					} else if ((sfnt_name.platform_id == TT_PLATFORM_MICROSOFT) && (sfnt_name.encoding_id == TT_MS_ID_UNICODE_CS)) {
						
						len = sfnt_name.string_len / 2;
						stringPtr.reset ((wchar_t*)malloc ((len + 1) * sizeof (wchar_t)));
						family_name = stringPtr.get ();
						
						for (i = 0; i < len; i++) {
							
							family_name[i] = ((wchar_t)sfnt_name.string[i * 2 + 1]) | (((wchar_t)sfnt_name.string[i * 2]) << 8);
							
						}
						
						family_name[len] = L'\0';
						return std::wstring (family_name, len);
						
					}
					
				}
				
			}
			
		}
		
		#endif
		
		return std::wstring ();
		
	}
	
	
	int Font::GetGlyphIndex (const char* character) {
		
		long charCode = readNextChar (character);
		
		return FT_Get_Char_Index ((FT_Face)face, charCode);
		 
	}
	
	
	value Font::GetGlyphIndices (const char* characters) {
		
		value indices = alloc_array (0);
		unsigned long character;
		int index;
		
		while (*characters != 0) {
			
			character = readNextChar (characters);
			index = FT_Get_Char_Index ((FT_Face)face, character);
			val_array_push (indices, alloc_int (index));
			
		}
		
		return indices;
		
	}
	
	
	value Font::GetGlyphMetrics (int index) {
		
		if (FT_Load_Glyph ((FT_Face)face, index, FT_LOAD_NO_BITMAP | FT_LOAD_DEFAULT) == 0) {
			
			value metrics = alloc_empty_object ();
			
			StringId* id = StringId::Get ();
			alloc_field (metrics, id->height, alloc_int (((FT_Face)face)->glyph->metrics.height));
			alloc_field (metrics, id->horizontalBearingX, alloc_int (((FT_Face)face)->glyph->metrics.horiBearingX));
			alloc_field (metrics, id->horizontalBearingY, alloc_int (((FT_Face)face)->glyph->metrics.horiBearingY));
			alloc_field (metrics, id->horizontalAdvance, alloc_int (((FT_Face)face)->glyph->metrics.horiAdvance));
			alloc_field (metrics, id->verticalBearingX, alloc_int (((FT_Face)face)->glyph->metrics.vertBearingX));
			alloc_field (metrics, id->verticalBearingY, alloc_int (((FT_Face)face)->glyph->metrics.vertBearingY));
			alloc_field (metrics, id->verticalAdvance, alloc_int (((FT_Face)face)->glyph->metrics.vertAdvance));
			
			return metrics;
			
		}
		
		return alloc_null ();
		
	}
	
	
	int Font::GetHeight () {
		
		return ((FT_Face)face)->height;
		
	}
	
	
	int Font::GetNumGlyphs () {
		
		return ((FT_Face)face)->num_glyphs;
		
	}
	
	
	int Font::GetUnderlinePosition () {
		
		return ((FT_Face)face)->underline_position;
		
	}
	
	
	int Font::GetUnderlineThickness () {
		
		return ((FT_Face)face)->underline_thickness;
		
	}
	
	
	int Font::GetUnitsPerEM () {
		
		return ((FT_Face)face)->units_per_EM;
		
	}
	
	
	value Font::RenderGlyph (int index, Bytes *imageData, int offset) {
		
		if (!imageData) {
			
			return alloc_null ();
			
		}
		
		GlyphImage *data = (GlyphImage*)(imageData->Data () + offset);
		
		if (FT_Load_Glyph ((FT_Face)face, index, FT_LOAD_RENDER) != 0)
		{
			
			data->width = 0;
			data->height = 0;
			data->x = 0;
			data->y = 0;
			return alloc_null ();
			
		}
		else
		{
			
			FT_Bitmap bitmap = ((FT_Face)face)->glyph->bitmap;
			
			data->width = bitmap.width;
			data->height = bitmap.rows;
			data->x = ((FT_Face)face)->glyph->bitmap_left;
			data->y = ((FT_Face)face)->glyph->bitmap_top;
			
			if (bitmap.width == 0 || bitmap.rows == 0)
				return alloc_null ();
			
			int width = bitmap.width;
			int height = bitmap.rows;
			Bytes image (bitmap.width * bitmap.rows);
			unsigned char* position = image.Data ();
			memcpy (position, bitmap.buffer, image.Length ());
			
			return image.Value ();
			
		}
		
	}
	
	
	value Font::RenderGlyphs (value indices, Bytes *imageData) {
		
		if (!imageData) {
			
			return alloc_null ();
			
		}
		
		int offset = 0;
		int totalOffset = 4;
		uint32_t count = 0;
		
		int numIndices = val_array_size (indices);
		int imageDataSize = (4 * 4) * numIndices;
		if (imageDataSize > imageData->Length ())
			imageData->Resize (imageDataSize);
		
		value images = alloc_array (numIndices);
		
		for (int i = 0; i < numIndices; i++) {
			
			value image = RenderGlyph (val_int (val_array_i (indices, i)), imageData, offset);
			val_array_set_i (images, i, image);
			offset += (4 * 4);
			
		}
		
		return images;
		
	}
	
	
	void Font::SetSize (size_t size) {
		
		size_t hdpi = 72;
		size_t vdpi = 72;
		
		FT_Set_Char_Size ((FT_Face)face, (int)(size*64), (int)(size*64), hdpi, vdpi);
		mSize = size;
		
	}
	
	
	Font* Font::Load (value data) {
		
		Font* font = NULL;
		
		#ifdef LIME_FREETYPE
		Resource resource;
		Bytes bytes;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			bytes.Set (data);
			resource = Resource (&bytes);
			
		}
		
		font = new Font (&resource, 0);
		
		if (font) {
			
			if (!font->face) {
				
				delete font;
				font = NULL;
				
			}
			
		}
		#endif
		
		return font;
		
	}
	
	
	value Font_to_val (Font* inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<Font>, Kinds::Get ()->Font);
		
	}
	
	
	Font* val_to_Font (value inHandle) {
		
		return lime_abstract_to_pointer<Font> (inHandle, Kinds::Get ()->Font);
		
	}
	
}
