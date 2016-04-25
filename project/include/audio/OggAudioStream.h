#ifndef LIME_OGG_AUDIO_STREAM_H
#define LIME_OGG_AUDIO_STREAM_H

#include <audio/AudioStream.h>
#include <vorbis/vorbisfile.h>

namespace lime {
	
	typedef struct {
		
		unsigned char* data;
		ogg_int64_t size;
		ogg_int64_t pos;
		
	} OAL_OggMemoryFile;
	
	class OggAudioStream : public AudioStream {
		
		
		public:
			
			~OggAudioStream ()
			{
				delete file;
				delete fakeFile;
			}
			
			OggAudioStream (OggVorbis_File *file, OAL_OggMemoryFile *fakeFile)
				: AudioStream (OggFormat), file (file), fakeFile (fakeFile) {}
			
			OggVorbis_File *file;
			OAL_OggMemoryFile *fakeFile;
			
	};
	
	
}


#endif