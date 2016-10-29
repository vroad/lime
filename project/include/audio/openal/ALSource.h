#ifndef LIME_AUDIO_OPENAL_AL_SOURCE_H
#define LIME_AUDIO_OPENAL_AL_SOURCE_H

#include <audio/openal/OpenALBindings.h>
#include <hx/CFFI.h>
#include <vector>
#include <map>

namespace lime {
	
	
	class ALSource {
		
	public:
		
		ALSource (ALCContextWrapper* contextWrapper, ALuint source);
		
		~ALSource ();
		
		void SetBuffer (value buffer);
		
		void AddQueuedBuffer (value inBuffer);
		
		value RemoveQueuedBufferById (ALuint id);
		
		ALuint source;
		
	private:
		
		AutoGCRoot* bufferRef;
		std::map<ALuint, AutoGCRoot*> queuedBuffers; 
		ALCContextWrapper* contextWrapper;
		
	};
	
	ALSource* val_to_ALSource (value inHandle);
	
	value ALSource_to_val (ALSource* inInstance);
	
	
}


#endif