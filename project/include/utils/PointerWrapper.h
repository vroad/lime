#ifndef LIME_UTILS_POINTER_WRAPPER_H
#define LIME_UTILS_POINTER_WRAPPER_H

#include <hx/CFFI.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {

	template <class T>
	void lime_pointer_destroy (value handle);
	
	struct PointerWrapperId {
			
		PointerWrapperId () {
			
			init = false;
			
		}
		
		int pointer;
		bool init;
		
	};
	
	static ThreadLocalStorage<PointerWrapperId> gPointerWrapperId;
	
	static void initializePointerWrapperId (PointerWrapperId &id) {
		
		id.pointer = val_id ("pointer");
		id.init = true;
		
	}
	
	template <class T>
	class PointerWrapper {
		
		public:
			
			PointerWrapper (T *pointer) {
				
				mPointer = pointer;
				mValue = alloc_empty_object ();
				PointerWrapperId id = gPointerWrapperId.Get ();
				
				if (id.init == false) {
					
					initializePointerWrapperId (id);
					gPointerWrapperId.Set (id);
					
				}
				
				alloc_field (mValue, id.pointer, alloc_float ((intptr_t)pointer));
				
			}
			
			PointerWrapper (value inValue) {
				
				PointerWrapperId id = gPointerWrapperId.Get ();
				
				if (id.init == false) {
					
					initializePointerWrapperId (id);
					gPointerWrapperId.Set (id);
					
				}
				
				mValue = inValue;
				mPointer = (T*)(intptr_t)val_float (val_field (inValue, id.pointer));
				
			}
			
			PointerWrapper () {
				
				mPointer = NULL;
				mValue = NULL;
				
			}
			
			T *mPointer;
			value mValue;
			
	};
	
	template <class T>
	T *GetPointer (value handle) {
		
		PointerWrapper<T> ptr (handle);
		return ptr.mPointer;
		
	}

	template <class T>
	value WrapPointer (T *pointer) {
		
		PointerWrapper<T> ptr (pointer);
		return ptr.mValue;
		
	}

	template <class T>
	value WrapPointerWithGC (T *pointer) {
		
		PointerWrapper<T> ptr (pointer);
		val_gc (ptr.mValue, lime_pointer_destroy<T>);
		return ptr.mValue;
		
	}

	template <class T>
	void lime_pointer_destroy (value handle) {
		
		PointerWrapper<T> ptr (handle);
		delete ptr.mPointer;
		
	}
	
}

#endif