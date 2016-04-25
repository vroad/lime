#ifndef LIME_AUDIO_FORMAT_OGG_H
#define LIME_AUDIO_FORMAT_OGG_H


#include <audio/AudioBuffer.h>
#include <utils/Resource.h>

class OggVorbis_File;

namespace lime {
	
	
	class OGG {
		
		
		public:
			
			static bool Decode (Resource *resource, AudioBuffer *audioBuffer, bool stream);
			static bool SeekStream (OggVorbis_File *oggFile, double seconds);
			static int DecodeStream (OggVorbis_File *oggFile, Bytes *data, int readSize, int writeOffset);
		
		
	};
	
	
}


#endif