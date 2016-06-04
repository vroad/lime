#ifndef LIME_UTILS_EXCEPTION_H
#define LIME_UTILS_EXCEPTION_H 

#include <hx/CFFI.h>

namespace lime {
	
	void ThrowException (const char *inStr) {
		
		value str = alloc_string (inStr);
		val_throw (str);
		
	}
	
}

#endif