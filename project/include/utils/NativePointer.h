#ifndef LIME_UTILS_NATIVE_POINTER_H
#define LIME_UTILS_NATIVE_POINTER_H

#include <hx/CFFI.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {
	
	template <class T>
	void lime_pointer_destroy (value handle);
	
	struct NativePointerId {
			
		NativePointerId () {
			
			init = false;
			
		}
		
		int pointer;
		bool init;
		
	};
	
	static ThreadLocalStorage<NativePointerId> gNativePointerId;
			
	static void initializeNativePointerId (NativePointerId &id) {
		
		id.pointer = val_id ("pointer");
		id.init = true;
		
	}
	
	template <class T>
	class NativePointer {
		
		public:
			
			NativePointer (T *pointer, bool setGC) {
				
				mPointer = pointer;
				mValue = alloc_empty_object ();
				NativePointerId id = gNativePointerId.Get ();
				
				if (id.init == false) {
					
					initializeNativePointerId (id);
					gNativePointerId.Set (id);
					
				}
				
				alloc_field (mValue, id.pointer, alloc_float ((intptr_t)pointer));
				
				if (setGC) {
					
					val_gc (mValue, lime_pointer_destroy<T>);
					
				}
				
			}
			
			NativePointer (value inValue) {
				
				NativePointerId id = gNativePointerId.Get ();
				
				if (id.init == false) {
					
					initializeNativePointerId (id);
					gNativePointerId.Set (id);
					
				}
				
				mValue = inValue;
				mPointer = (T*)(intptr_t)val_float (val_field (inValue, id.pointer));
				
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