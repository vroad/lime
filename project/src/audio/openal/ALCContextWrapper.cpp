#include <audio/openal/ALCContextWrapper.h>

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
	
}