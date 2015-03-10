#include <text/Font.h>
#include <graphics/ImageBuffer.h>
#include <system/System.h>

#include <algorithm>
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
#define IS_IN_RANGE(c, f, l)	 (((c) >= (f)) && ((c) <= (l)))


unsigned long readNextChar (char*& p)
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
		PT_CURVE = 3
		
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
		
		// Cubic curves are not supported, we need to approximate to a quadratic
		// TODO: divide into multiple curves
		
		glyph *g = static_cast<glyph*> (user);
		
		FT_Vector ctl;
		ctl.x = (-0.25 * g->x) + (0.75 * ctl1->x) + (0.75 * ctl2->x) + (-0.25 * to->x);
		ctl.y = (-0.25 * g->y) + (0.75 * ctl1->y) + (0.75 * ctl2->y) + (-0.25 * to->y);
		
		g->pts.push_back (PT_CURVE);
		g->pts.push_back (ctl.x - g->x);
		g->pts.push_back (ctl.y - g->y);
		g->pts.push_back (to->x - ctl.x);
		g->pts.push_back (to->y - ctl.y);
		
		g->x = to->x;
		g->y = to->y;
		
		return 0;
		
	}
	
	
}


namespace lime {
	
	
	static int id_height;
	static int id_horizontalAdvance;
	static int id_horizontalBearingX;
	static int id_horizontalBearingY;
	static int id_index;
	static int id_offset;
	static int id_size;
	static int id_verticalAdvance;
	static int id_verticalBearingX;
	static int id_verticalBearingY;
	static int id_width;
	static int id_x;
	static int id_y;
	static int id_bitmap;
	static bool init = false;
	static FT_Library library;
	static int libRefCount = 0;
	
	bool CompareGlyphHeight (const GlyphInfo &a, const GlyphInfo &b) {
		
		return a.height > b.height;
		
	}
	
	
	bool CompareGlyphCodepoint (const GlyphInfo &a, const GlyphInfo &b) {
		
		return a.codepoint < b.codepoint && a.size < b.size;
		
	}
	
	
	static void initialize () {
		
		if (!init) {
			
			id_width = val_id ("width");
			id_height = val_id ("height");
			id_x = val_id ("x");
			id_y = val_id ("y");
			id_offset = val_id ("offset");
			id_size = val_id ("size");
			
			id_horizontalAdvance = val_id ("horizontalAdvance");
			id_horizontalBearingX = val_id ("horizontalBearingX");
			id_horizontalBearingY = val_id ("horizontalBearingY");
			id_index = val_id ("index");
			id_verticalAdvance = val_id ("verticalAdvance");
			id_verticalBearingX = val_id ("verticalBearingX");
			id_verticalBearingY = val_id ("verticalBearingY");

			id_bitmap = val_id ("bitmap");
			
			init = true;
			
		}
		
	}
	
	Font::Font (Resource *resource, int faceIndex) {

		int error;
	
		if (libRefCount < 1)
			error = FT_Init_FreeType (&library);
		else
			error = 0;

		libRefCount++;
		
		if (resource) {
			
			if (error) {
				
				printf ("Could not initialize FreeType\n");
				
			} else {
				
				FT_Face face;
				FILE_HANDLE *file = NULL;
				
				if (resource->path) {
					
					file = lime::fopen (resource->path, "rb");
					
					if (file->isFile ()) {
						
						error = FT_New_Face (library, resource->path, faceIndex, &face);
						
					} else {
						
						ByteArray data = ByteArray (resource->path);
						unsigned char *buffer = (unsigned char*)malloc (data.Size ());
						memcpy (buffer, data.Bytes (), data.Size ());
						error = FT_New_Memory_Face (library, buffer, data.Size (), faceIndex, &face);
						
					}
					
				} else {
					
					unsigned char *buffer = (unsigned char*)malloc (resource->data->Size ());
					memcpy (buffer, resource->data->Bytes (), resource->data->Size ());
					error = FT_New_Memory_Face (library, buffer, resource->data->Size (), faceIndex, &face);
					
				}
				
				if (file) {
					
					lime::fclose (file);
					
				}
				
				if (error == FT_Err_Unknown_File_Format) {
					
					printf ("Invalid font type\n");
					
				} else if (error) {
					
					printf ("Failed to load font face %s\n", resource->path);
					
				} else {
					
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
		
		if (face) {
			
			//FT_Done_Face ((FT_Face)face);
			
		}
		
	}
	
	
	value Font::Decompose (int em) {
		
		int result, i, j;
		
		FT_Face face = (FT_Face)this->face;
		FT_Set_Char_Size (face, em, em, 72, 72);
		
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
		
		char_code = FT_Get_First_Char (face, &glyph_index);
		
		while (glyph_index != 0) {
			
			if (FT_Load_Glyph (face, glyph_index, FT_LOAD_NO_BITMAP | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_DEFAULT) == 0) {
				
				glyph *g = new glyph;
				result = FT_Outline_Decompose (&face->glyph->outline, &ofn, g);
				
				if (result == 0) {
					
					g->index = glyph_index;
					g->char_code = char_code;
					g->metrics = face->glyph->metrics;
					glyphs.push_back (g);
					
				} else {
					
					delete g;
					
				}
				
			}
			
			char_code = FT_Get_Next_Char (face, char_code, &glyph_index);
			
		}
		
		// Ascending sort by character codes
		std::sort (glyphs.begin (), glyphs.end (), glyph_sort_predicate ());
		
		std::vector<kerning>  kern;
		if (FT_HAS_KERNING (face)) {
			
			int n = glyphs.size ();
			FT_Vector v;
			
			for (i = 0; i < n; i++) {
				
				int  l_glyph = glyphs[i]->index;
				
				for (j = 0; j < n; j++) {
					
					int r_glyph = glyphs[j]->index;
					
					FT_Get_Kerning (face, l_glyph, r_glyph, FT_KERNING_DEFAULT, &v);
					
					if (v.x != 0 || v.y != 0) {
						
						kern.push_back (kerning (i, j, v.x, v.y));
						
					}
					
				}
				
			}
			
		}
		
		int num_glyphs = glyphs.size ();
		wchar_t* family_name = GetFamilyName();
		
		value ret = alloc_empty_object ();
		alloc_field (ret, val_id ("has_kerning"), alloc_bool (FT_HAS_KERNING (face)));
		alloc_field (ret, val_id ("is_fixed_width"), alloc_bool (FT_IS_FIXED_WIDTH (face)));
		alloc_field (ret, val_id ("has_glyph_names"), alloc_bool (FT_HAS_GLYPH_NAMES (face)));
		alloc_field (ret, val_id ("is_italic"), alloc_bool (face->style_flags & FT_STYLE_FLAG_ITALIC));
		alloc_field (ret, val_id ("is_bold"), alloc_bool (face->style_flags & FT_STYLE_FLAG_BOLD));
		alloc_field (ret, val_id ("num_glyphs"), alloc_int (num_glyphs));
		alloc_field (ret, val_id ("family_name"), family_name == NULL ? alloc_string (face->family_name) : alloc_wstring (family_name));
		alloc_field (ret, val_id ("style_name"), alloc_string (face->style_name));
		alloc_field (ret, val_id ("em_size"), alloc_int (face->units_per_EM));
		alloc_field (ret, val_id ("ascend"), alloc_int (face->ascender));
		alloc_field (ret, val_id ("descend"), alloc_int (face->descender));
		alloc_field (ret, val_id ("height"), alloc_int (face->height));
		
		delete family_name;
		
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
		if (FT_HAS_KERNING (face)) {
			
			value neko_kerning = alloc_array (kern.size ());
			
			for (i = 0; i < kern.size(); i++) {
				
				kerning *k = &kern[i];
				
				value item = alloc_empty_object();
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


	value Font::GetFaceInfo () {

		wchar_t* family_name = GetFamilyName();
		value ret = alloc_empty_object ();
		FT_Face face = (FT_Face)this->face;
		alloc_field (ret, val_id ("has_kerning"), alloc_bool (FT_HAS_KERNING (face)));
		alloc_field (ret, val_id ("is_fixed_width"), alloc_bool (FT_IS_FIXED_WIDTH (face)));
		alloc_field (ret, val_id ("has_glyph_names"), alloc_bool (FT_HAS_GLYPH_NAMES (face)));
		alloc_field (ret, val_id ("is_italic"), alloc_bool (face->style_flags & FT_STYLE_FLAG_ITALIC));
		alloc_field (ret, val_id ("is_bold"), alloc_bool (face->style_flags & FT_STYLE_FLAG_BOLD));
		alloc_field (ret, val_id ("num_glyphs"), alloc_int(0));
		alloc_field (ret, val_id ("family_name"), family_name == NULL ? alloc_string (face->family_name) : alloc_wstring (family_name));
		alloc_field (ret, val_id ("style_name"), alloc_string (face->style_name));
		alloc_field (ret, val_id ("em_size"), alloc_int (face->units_per_EM));
		alloc_field (ret, val_id ("ascend"), alloc_int (face->ascender));
		alloc_field (ret, val_id ("descend"), alloc_int (face->descender));
		alloc_field (ret, val_id ("height"), alloc_int (face->height));
		
		delete family_name;
		
		// 'glyphs' field
		value neko_glyphs = alloc_null();
		alloc_field (ret, val_id ("glyphs"), neko_glyphs);
		
		// 'kerning' field
		alloc_field (ret, val_id ("kerning"), alloc_null ());
		
		return ret;
		
	}
	
	int Font::GetAscender () {
		
		return ((FT_Face)face)->ascender;
		
	}
	
	
	int Font::GetDescender () {
		
		return ((FT_Face)face)->descender;
		
	}
	
	
	wchar_t *Font::GetFamilyName () {
		
		#ifdef LIME_FREETYPE
		
		wchar_t *family_name = NULL;
		FT_SfntName sfnt_name;
		FT_UInt num_sfnt_names, sfnt_name_index;
		int len, i;
		
		if (FT_IS_SFNT (((FT_Face)face))) {
			
			num_sfnt_names = FT_Get_Sfnt_Name_Count ((FT_Face)face);
			sfnt_name_index = 0;
			
			while (sfnt_name_index < num_sfnt_names) {
				
				if (!FT_Get_Sfnt_Name ((FT_Face)face, sfnt_name_index++, (FT_SfntName *)&sfnt_name) && sfnt_name.name_id == TT_NAME_ID_FULL_NAME) {
					
					if (sfnt_name.platform_id == TT_PLATFORM_MACINTOSH) {
						
						len = sfnt_name.string_len;
						family_name = new wchar_t[len + 1];
						mbstowcs (&family_name[0], &reinterpret_cast<const char*>(sfnt_name.string)[0], len);
						family_name[len] = L'\0';
						return family_name;
						
					} else if ((sfnt_name.platform_id == TT_PLATFORM_MICROSOFT) && (sfnt_name.encoding_id == TT_MS_ID_UNICODE_CS)) {
						
						len = sfnt_name.string_len / 2;
						family_name = (wchar_t*)malloc ((len + 1) * sizeof (wchar_t));
						
						for (i = 0; i < len; i++) {
							
							family_name[i] = ((wchar_t)sfnt_name.string[i * 2 + 1]) | (((wchar_t)sfnt_name.string[i * 2]) << 8);
							
						}
						
						family_name[len] = L'\0';
						return family_name;
						
					}
					
				}
				
			}
			
		}
		
		#endif
		
		return NULL;
		
	}
	
	
	void GetGlyphMetrics_Push (FT_Face face, FT_UInt glyphIndex, value glyphList) {
		
		if (FT_Load_Glyph (face, glyphIndex, FT_LOAD_NO_BITMAP | FT_LOAD_FORCE_AUTOHINT | FT_LOAD_DEFAULT) == 0) {
			
			value metrics = alloc_empty_object ();
			
			alloc_field (metrics, id_height, alloc_int (((FT_Face)face)->glyph->metrics.height));
			alloc_field (metrics, id_horizontalBearingX, alloc_int (((FT_Face)face)->glyph->metrics.horiBearingX));
			alloc_field (metrics, id_horizontalBearingY, alloc_int (((FT_Face)face)->glyph->metrics.horiBearingY));
			alloc_field (metrics, id_horizontalAdvance, alloc_int (((FT_Face)face)->glyph->metrics.horiAdvance));
			alloc_field (metrics, id_index, alloc_int (glyphIndex));
			alloc_field (metrics, id_verticalBearingX, alloc_int (((FT_Face)face)->glyph->metrics.vertBearingX));
			alloc_field (metrics, id_verticalBearingY, alloc_int (((FT_Face)face)->glyph->metrics.vertBearingY));
			alloc_field (metrics, id_verticalAdvance, alloc_int (((FT_Face)face)->glyph->metrics.vertAdvance));
			
			val_array_push (glyphList, metrics);
			
		}
		
	}
	
	
	value Font::GetGlyphMetrics (GlyphSet *glyphSet) {
		
		initialize ();
		
		value glyphList = alloc_array (0);
		
		if (!glyphSet->glyphs.empty ()) {
			
			for (unsigned int i = 0; i < glyphSet->glyphs.length (); i++) {
				
				GetGlyphMetrics_Push ((FT_Face)face, FT_Get_Char_Index ((FT_Face)face, glyphSet->glyphs[i]), glyphList);
				
			}
			
		}
		
		GlyphRange range;
		
		for (int i = 0; i < glyphSet->ranges.size (); i++) {
			
			range = glyphSet->ranges[i];
			
			if (range.start == 0 && range.end == -1) {
				
				FT_UInt glyphIndex;
				FT_ULong charCode = FT_Get_First_Char ((FT_Face)face, &glyphIndex);
				
				while (glyphIndex != 0) {
					
					GetGlyphMetrics_Push ((FT_Face)face, glyphIndex, glyphList);
					charCode = FT_Get_Next_Char ((FT_Face)face, charCode, &glyphIndex);
					
				}
				
			} else {
				
				unsigned long end = range.end;
				
				if (end < 0) {
					
					end = ((FT_Face)face)->num_glyphs - 1;
					
				}
				
				for (unsigned long i = range.start; i <= end; i++) {
					
					GetGlyphMetrics_Push ((FT_Face)face, i, glyphList);
					
				}
				
			}
			
		}
		
		return glyphList;
		
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
	
	
	void Font::SetSize (size_t size) {
		
		size_t hdpi = 72;
		size_t vdpi = 72;
		size_t hres = 100;
		FT_Matrix matrix = {
			(int)((1.0/hres) * 0x10000L),
			(int)((0.0) * 0x10000L),
			(int)((0.0) * 0x10000L),
			(int)((1.0) * 0x10000L)
		};
		
		FT_Set_Char_Size ((FT_Face)face, 0, (int)(size*64), (int)(hdpi * hres), vdpi);
		FT_Set_Transform ((FT_Face)face, &matrix, NULL);
		
		mSize = size;
		
	}
	
	
	value Font::RenderToImage (size_t size, const char *glyphs) {
		
		initialize ();
		
		if (mSize != size)
			SetSize(size);

		char *g = (char*)glyphs;
		size_t glyphCount = 0;
		while (*g != 0) {
			readNextChar(g);
			glyphCount++;
		}
		
		value rects = alloc_array (glyphCount);
		int rectsIndex = 0;

		g = (char*)glyphs;
		FT_Face face = (FT_Face)this->face;
		while (*g != 0) {
			
			FT_ULong charCode = readNextChar(g);
			FT_UInt index = FT_Get_Char_Index (face, charCode);
			
			FT_Load_Glyph (face, index, FT_LOAD_DEFAULT);
			
			if (FT_Render_Glyph (face->glyph, FT_RENDER_MODE_NORMAL) != 0) continue;
			
			FT_Bitmap bitmap = face->glyph->bitmap;
			
			value v = alloc_empty_object ();
			size_t buf_len = bitmap.width * bitmap.rows;
			if (buf_len != 0)
			{
				ByteArray ba(buf_len);
				memcpy(ba.Bytes(), bitmap.buffer, buf_len);
				alloc_field(v, id_bitmap, ba.mValue);
			}
			else
				alloc_field(v, id_bitmap, alloc_null());
			alloc_field (v, id_width, alloc_int (bitmap.width));
			alloc_field (v, id_height, alloc_int (bitmap.rows));
			
			alloc_field (v, id_x, alloc_int (face->glyph->bitmap_left));
			alloc_field (v, id_y, alloc_int (face->glyph->bitmap_top));

			alloc_field (v, val_id ("advance"), alloc_int (face->glyph->metrics.horiAdvance));
			alloc_field (v, val_id ("min_x"), alloc_int (face->glyph->metrics.horiBearingX));
			alloc_field (v, val_id ("max_x"), alloc_int (face->glyph->metrics.horiBearingX + face->glyph->metrics.width));
			alloc_field (v, val_id ("min_y"), alloc_int (face->glyph->metrics.horiBearingY - face->glyph->metrics.height));
			alloc_field (v, val_id ("max_y"), alloc_int (face->glyph->metrics.horiBearingY));
			
			val_array_set_i (rects, rectsIndex++, v);

		}
		
		return rects;
		
	}

	value Font::GetKernings(value glyphs)
	{
		return alloc_null();
	}
	
	
}
