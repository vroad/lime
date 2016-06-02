#ifndef LIME_AUDIO_OPENAL_ALC_CONTEXT_WRAPPER_H
#define LIME_AUDIO_OPENAL_ALC_CONTEXT_WRAPPER_H

#include <hx/CFFI.h>
#include <memory>

#if defined(HX_MACOS) || defined(IPHONE)
#include <OpenAL/alc.h>
#else
#include "AL/alc.h"
#endif

namespace lime {
	
	class ALCContextWrapper {
		
	public:
		
		ALCContextWrapper (ALCcontext* context, value device);
		
		~ALCContextWrapper ();
		
		ALCcontext* alcContext;
		std::unique_ptr<AutoGCRoot> alcDevice;
		
	};
	
	
}


#endif