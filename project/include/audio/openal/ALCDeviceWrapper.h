#ifndef LIME_AUDIO_OPENAL_ALC_DEVICE_WRAPPER_H
#define LIME_AUDIO_OPENAL_ALC_DEVICE_WRAPPER_H

#include <audio/openal/OpenALBindings.h>
#include <hx/CFFI.h>

namespace lime {
	
	class ALCDeviceWrapper {
		
	public:
		
		~ALCDeviceWrapper ();
		
		static ALCDeviceWrapper* Create (const char* deviceName);
		
		void AddRef ();
		
		void Release ();
		
		ALCdevice* alcDevice;
		
	private:
		
		ALCDeviceWrapper ();
		
		bool Init (const char* deviceName);
		
		int refCount;
		
	};
	
	ALCDeviceWrapper* val_to_ALCDeviceWrapper (value inHandle);
	
	value ALCDeviceWrapper_to_val (ALCDeviceWrapper* inInstance);
	
	
}


#endif