#ifndef LIME_GRAPHICS_FONT_H
#define LIME_GRAPHICS_FONT_H


#include <hx/CFFI.h>
#include <utils/Resource.h>

#ifdef LIME_FREETYPE
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_SFNT_NAMES_H
#include FT_TRUETYPE_IDS_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#endif


namespace lime {
	
	
	class Image;
	
	
	typedef struct {
		
		unsigned long codepoint;
		size_t size;
	#ifdef LIME_FREETYPE
		FT_UInt index;
		FT_Pos height;
	#else
		int index;
		int height;
	#endif
		
	} GlyphInfo;
	
	
	class Font {
		
		
		public:
			
			static Font *FromFile (Resource *resource);
			~Font();
			
			value Decompose (int em);
			value GetFaceInfo ();
			value GetFamilyName ();
			value GetGlyphInfo (const char *glyphs);
			value RenderToImage (size_t size, const char *glyphs);
			value GetKernings (value glyphs);
			void SetSize (size_t size);

			#ifdef LIME_FREETYPE
			Font (FT_Face face, FT_Byte *data);
			FT_Face face;
			FT_Byte *data;
			#else
			void *face;
			void *data;
			#endif
			
		private:
			
			size_t mSize;
		
	};
	
	
}


#endif
