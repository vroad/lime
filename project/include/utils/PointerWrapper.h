#ifndef LIME_UTILS_POINTER_WRAPPER_H
#define LIME_UTILS_POINTER_WRAPPER_H

#include <hx/CFFI.h>

namespace lime {
	
	template <class T>
	void lime_pointer_destroy (value handle);
	
	template <class T>
	value WrapPointerInternal (T *pointer, vkind kind) {
		
		if (pointer == NULL)
			return alloc_null ();
		return alloc_abstract (kind, pointer);
		
	}

	template <class T>
	T *GetPointer (value handle) {
		
		T::unimplemented ();
		
	}
	
	template <class T>
	value WrapPointer (T *pointer) {
		
		T::unimplemented ();
		
	}

	template <class T>
	value WrapPointerWithGC (T *pointer) {
		
		value outValue = WrapPointer<T> (pointer);
		val_gc (outValue, lime_pointer_destroy<T>);
		return outValue;
		
	}

	template <class T>
	void lime_pointer_destroy (value handle) {
		
		T *ptr = (T*)val_data (handle);
		delete ptr;
		free_abstract (handle);
		
	}
	
}

#endif