#ifndef LIME_AUDIO_FORMAT_OGG_H
#define LIME_AUDIO_FORMAT_OGG_H


#include <audio/AudioBuffer.h>
#include <utils/Resource.h>

class OggVorbis_File;

namespace lime {
	
	
	class OGG {
		
		
		public:
			
			static bool Decode (Resource *resource, AudioBuffer *audioBuffer, OggVorbis_File *oggFile, bool stream);
			static value DecodeStream (OggVorbis_File *oggFile, int sizeInBytes, int bufferCount);
		
		
	};
	
	
}


#endif