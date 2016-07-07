#include <system/CFFIPointer.h>


namespace lime {
	
	
	value CFFIPointer (void* ptr, hx::finalizer finalizer, vkind kind) {
		
		if (ptr) {
			
			value handle = kind != 0 ? alloc_abstract (kind, ptr) : cffi::alloc_pointer (ptr);
			
			if (finalizer) {
				
				val_gc (handle, finalizer);
				
			}
			
			return handle;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
}