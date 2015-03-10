#ifndef LIME_TEXT_TEXT_ENGINE_H
#define LIME_TEXT_TEXT_ENGINE_H


#include <text/Font.h>
#include <hx/CFFI.h>


namespace lime {
	
	
	class TextEngine {
		
		
		public:
			
			TextEngine (int direction, const char *script, const char *language);
			~TextEngine ();
			
			value Layout (Font *font, size_t size, const char *text);
			
		private:
			
			void *mBuffer;
			long mDirection;
			long mScript;
			long mLanguage;
			
	};
	
	
}


#endif
