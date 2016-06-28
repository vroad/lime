#include <app/Application.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {
	
	
	value Application_to_val (Application *inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<Application>, Kinds::Get ()->Application);
		
	}
	
	lime::Application* val_to_Application (value inHandle) {
		
		return lime_abstract_to_pointer<Application> (inHandle, Kinds::Get ()->Application);
		
	}
	
	
}