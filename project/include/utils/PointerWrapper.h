#ifndef LIME_UTILS_POINTER_WRAPPER_H
#define LIME_UTILS_POINTER_WRAPPER_H

#include <hx/CFFI.h>

namespace lime {
	
	template <class T>
	void lime_pointer_destroy (value handle) {
		
		T *ptr = (T*)val_data (handle);
		delete ptr;
		//free_abstract (handle);
		
	}
	
}

#endif