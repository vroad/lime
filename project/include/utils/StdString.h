#ifndef LIME_UTILS_STD_STRING_H
#define LIME_UTILS_STD_STRING_H

#include <hx/CFFI.h>
#include <string>

namespace lime {
	
	value StdWString_to_val (const std::wstring& inString) {
		
		return alloc_wstring_len (inString.c_str (), inString.size ());
		
	}
	
}

#endif