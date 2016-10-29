#ifndef LIME_AUDIO_OPENAL_AL_BUFFER_H
#define LIME_AUDIO_OPENAL_AL_BUFFER_H

#include <audio/openal/OpenALBindings.h>
#include <hx/CFFI.h>


namespace lime {
	
	
	class ALCContextWrapper;
	
	class ALBuffer {
		
	public:
		
		ALBuffer (ALCContextWrapper* contextWrapper, ALuint buffer);
		
		~ALBuffer ();
		
		ALCContextWrapper* contextWrapper;
		ALuint buffer;
		
	};
	
	ALBuffer* val_to_ALBuffer (value inHandle);
	
	value ALBuffer_to_val (ALBuffer* inInstance);
	
	
}


#endif