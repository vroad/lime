#include <ui/Window.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {
	
	value Window_to_val (Window *inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<Window>, Kinds::Get ()->Window);
		
	}
	
	Window* val_to_Window (value inHandle) {
		
		return lime_abstract_to_pointer<Window> (inHandle, Kinds::Get ()->Window);
		
	}
	
}