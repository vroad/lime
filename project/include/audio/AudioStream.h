#ifndef LIME_AUDIO_STREAM_H
#define LIME_AUDIO_STREAM_H

#include <audio/AudioFormat.h>

namespace lime {
	
	class AudioStream {
		
		
		public:
			
			AudioStream(AudioFormat format, void *handle)
				: format(format), handle(handle) {}
			
			AudioFormat format;
			void *handle;


	};
	
	
}


#endif