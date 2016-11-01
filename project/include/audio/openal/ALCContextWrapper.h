#ifndef LIME_AUDIO_OPENAL_ALC_CONTEXT_WRAPPER_H
#define LIME_AUDIO_OPENAL_ALC_CONTEXT_WRAPPER_H

#include <audio/openal/OpenALBindings.h>
#include <hx/CFFI.h>
#include <vector>

namespace lime {
	
	
	class ALCContextWrapper {
		
	public:
		
		ALCContextWrapper (ALCcontext* context, ALCDeviceWrapper* deviceWrapper);
		
		~ALCContextWrapper ();
		
		void AddRef ();
		
		void Release ();
		
		void Dispose ();
		
		ALCcontext* alcContext;
		ALCDeviceWrapper* deviceWrapper;
		bool disposed;
		int refCount;
		
	};
	
	void release_ALCContextWrapper (ALCContextWrapper* wrapper);
	
	ALCContextWrapper* val_to_ALCContextWrapper (value inHandle);
	
	value ALCContextWrapper_to_val (ALCContextWrapper* inInstance);
	
	
}


#endif