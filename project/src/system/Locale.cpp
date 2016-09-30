#include <system/Locale.h>

#if defined(HX_WINDOWS)
#include <windows.h>
#elif defined(HX_LINUX)
#include <stdlib.h>
#include <string.h>
#include <clocale>
#endif


namespace lime {
	
	
	value Locale::GetSystemLocale () {
		
		#if defined(HX_WINDOWS)
		
		wchar_t locale[9];
		int length = GetLocaleInfo (GetSystemDefaultUILanguage (), LOCALE_SISO639LANGNAME, &locale[0], sizeof (locale));
		return alloc_wstring_len (locale, length);
		
		#elif defined(HX_LINUX)
		
		const char* locale = getenv ("LANG");
		
		if (!locale) {
			
			locale = setlocale (LC_ALL, "");
			
		}
		
		if (locale) {
			
			return alloc_string (locale);
			
		}
		
		return 0;
		
		#else
		
		return 0;
		
		#endif
		
	}
	
	
}