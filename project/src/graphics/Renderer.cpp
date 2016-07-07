#include <graphics/Renderer.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {

	value Renderer_to_val (Renderer *inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<Renderer>, Kinds::Get ()->Renderer);
		
	}
	
	Renderer* val_to_Renderer (value inHandle) {
		
		return lime_abstract_to_pointer<Renderer> (inHandle, Kinds::Get ()->Renderer);
		
	}
	
}