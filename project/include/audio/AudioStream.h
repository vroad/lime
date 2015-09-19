#ifndef LIME_AUDIO_STREAM_H
#define LIME_AUDIO_STREAM_H

#include <audio/AudioFormat.h>

namespace lime {
	
	class AudioStream {
		
		
		public:

			virtual ~AudioStream() {}
			
			AudioStream(AudioFormat format)
				: format(format) {}
			
			AudioFormat format;


	};
	
	
}


#endif