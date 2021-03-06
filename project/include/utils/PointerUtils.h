#ifndef LIME_UTILS_POINTER_UTILS_H
#define LIME_UTILS_POINTER_UTILS_H

#include <hx/CFFI.h>
#include <system/CFFIPointer.h>

namespace lime {
	
	template <class T>
	void lime_destroy_abstract (value handle) {
		
		T *ptr = (T*)val_data (handle);
		delete ptr;
		free_abstract (handle);
		
	}
	
	template <class T>
	T* lime_abstract_to_pointer (value inHandle, vkind kind) {
		
		T* instance = (T*) val_to_kind (inHandle, kind);
		return instance;
		
	}
	
}

#endif