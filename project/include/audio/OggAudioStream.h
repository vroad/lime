#ifndef LIME_OGG_AUDIO_STREAM_H
#define LIME_OGG_AUDIO_STREAM_H

#include <audio/AudioStream.h>
#include <vorbis/vorbisfile.h>

namespace lime {
	
	class OggAudioStream : public AudioStream {
		
		
		public:
			
			~OggAudioStream()
			{
				delete file;
			}
			
			OggAudioStream(OggVorbis_File *file)
				: AudioStream(OggFormat), file(file) {}
			
			OggVorbis_File *file;
			
	};
	
	
}


#endif