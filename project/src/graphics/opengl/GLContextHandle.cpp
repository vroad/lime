#include <graphics/opengl/GLContextHandle.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>
	
namespace lime {
	
	value GLContextHandle_to_value (GLContextHandle *inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<GLContextHandle>, Kinds::Get ()->GLContextHandle);
		
	}
	
	GLContextHandle* val_to_GLContextHandle (value inHandle) {
		
		return lime_abstract_to_pointer<GLContextHandle> (inHandle, Kinds::Get ()->GLContextHandle);
		
	}
	
}