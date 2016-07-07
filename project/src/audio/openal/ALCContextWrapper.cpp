#include <audio/openal/ALCContextWrapper.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {
	
	ALCContextWrapper::ALCContextWrapper (ALCcontext* context, value device) {
		
		alcContext = context;
		alcDevice.reset (new AutoGCRoot (device));
		
	}
	
	ALCContextWrapper::~ALCContextWrapper () {
		
		ALCcontext* currentContext = alcGetCurrentContext();
		alcMakeContextCurrent (NULL);
		alcDestroyContext (alcContext);
		alcMakeContextCurrent (currentContext);
		
	}
	
	ALCContextWrapper* val_to_ALCContextWrapper (value inHandle) {
		
		return lime_abstract_to_pointer<ALCContextWrapper> (inHandle, Kinds::Get ()->ALCContextWrapper);
		
	}
	
	value ALCContextWrapper_to_val (ALCContextWrapper* inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<ALCContextWrapper>, Kinds::Get ()->ALCContextWrapper);
		
	}
	
}