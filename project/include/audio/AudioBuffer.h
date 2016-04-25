#ifndef LIME_AUDIO_AUDIO_BUFFER_H
#define LIME_AUDIO_AUDIO_BUFFER_H


#include <hx/CFFI.h>
#include <utils/Bytes.h>
#include <audio/AudioStream.h>

#ifdef ANDROID
#include <android/log.h>
#endif


#ifdef ANDROID
#define LOG_SOUND(args,...) __android_log_print(ANDROID_LOG_INFO, "Lime", args, ##__VA_ARGS__)
#else
#ifdef IPHONE
//#define LOG_SOUND(args,...) printf(args, ##__VA_ARGS__)
#define LOG_SOUND(args...) { }
#elif defined(TIZEN)
#include <FBase.h>
#define LOG_SOUND(args,...) AppLog(args, ##__VA_ARGS__)
#else
#define LOG_SOUND(args,...) printf(args, ##__VA_ARGS__)
#endif
#endif
//#define LOG_SOUND(args...)  { }


namespace lime {
	
	struct AudioBufferId {
		
		AudioBufferId () {
			
			init = false;
			
		}
		
		int bitsPerSample;
		int channels;
		int handle;
		int sourceData;
		int data;
		int sampleRate;
		int length;
		bool init;
		
	};
	
	AudioBufferId GetAudioBufferId ();
	
	class AudioBuffer {
		
		
		public:
			
			AudioBuffer ();
			~AudioBuffer ();
			
			value Value ();
			
			int bitsPerSample;
			int channels;
			int sampleRate;
			int length;
			AudioStream *handle;
			Bytes *sourceData;
			Bytes *data;
			
		private:
			
			value mValue;
		
		
	};
	
	
}


#endif