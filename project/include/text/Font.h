#ifndef LIME_TEXT_FONT_H
#define LIME_TEXT_FONT_H


#include <graphics/ImageBuffer.h>
#include <utils/Resource.h>
#include <hx/CFFI.h>
#include <list>


namespace lime {
	
	
	class Image;
	
	
	typedef struct {
		
		unsigned long codepoint;
		size_t size;
		int index;
		int height;
		
	} GlyphInfo;
	
	
	class Font {
		
		
		public:
			
			Font (void* face = 0);
			Font (Resource *resource, int faceIndex = 0);
			~Font ();
			
			value Decompose (int em);
			value GetFaceInfo ();
			wchar_t *GetFamilyName ();
			value GetGlyphInfo (const char *glyphs);
			value RenderToImage (size_t size, const char *glyphs);
			value GetKernings (value glyphs);
			void SetSize (size_t size);
			
			void* face;
			
		private:
			
			
			size_t mSize;
		
	};
	
	
}


#endif
