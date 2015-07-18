#ifndef LIME_UTILS_NATIVE_POINTER_H
#define LIME_UTILS_NATIVE_POINTER_H

#include <hx/CFFI.h>

namespace lime {
	
	template <class T>
	void lime_pointer_destroy (value handle);
	
	template <class T>
	class NativePointer {
		
		public:
			
			NativePointer (T *pointer, bool setGC) {
				
				mPointer = pointer;
				mValue = alloc_empty_object ();
				alloc_field (mValue, val_id ("pointer"), alloc_float ((intptr_t)pointer));
				if (setGC) {

					val_gc (mValue, lime_pointer_destroy<T>);

				}

			}
			
			NativePointer (value inValue) {
				
				mValue = inValue;
				mPointer = (T*)(intptr_t)val_float (val_field (inValue, val_id ("pointer")));
				
			}
			
			NativePointer () {
				
				mPointer = NULL;
				mValue = NULL;
				
			}
			
			T *mPointer;
			value mValue;
			
	};
	
	template <class T>
	T *GetNativePointer (value handle) {
		
		NativePointer<T> ptr (handle);
		return ptr.mPointer;
		
	}

	template <class T>
	value CreateNativePointer (T *pointer, bool setGC = true) {
		
		NativePointer<T> ptr (pointer, setGC);
		return ptr.mValue;
		
	}
	
	template <class T>
	void lime_pointer_destroy (value handle) {
		
		NativePointer<T> ptr (handle);
		delete ptr.mPointer;
		
	}
	
}

#endif