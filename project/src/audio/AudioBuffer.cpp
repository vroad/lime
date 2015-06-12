#include <audio/AudioBuffer.h>
#include <utils/NativePointer.h>
#include <utils/ThreadLocalStorage.h>

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
		bool init;
	
	};

	static ThreadLocalStorage<AudioBufferId> stringId;

	AudioBuffer::AudioBuffer () {
		
		bitsPerSample = 0;
		channels = 0;
		handle = NULL;
		sourceData = NULL;
		data = new ByteArray ();
		sampleRate = 0;
		
	}
	
	
	AudioBuffer::~AudioBuffer () {
		
		delete sourceData;
		delete data;
		
	}
	
	
	value AudioBuffer::Value () {
		
		AudioBufferId id = stringId.Get ();
		if (!id.init) {
			
			id.bitsPerSample = val_id ("bitsPerSample");
			id.channels = val_id ("channels");
			id.handle = val_id ("handle");
			id.sourceData = val_id ("sourceData");
			id.data = val_id ("data");
			id.sampleRate = val_id ("sampleRate");
			id.init = true;
			stringId.Set (id);
			
		}
		
		value handleValue;
		if (handle != NULL) {
			
			NativePointer<AudioStream> ptr (handle);
			handleValue = ptr.mValue;
			
		} else {
			
			handleValue = alloc_null ();
			
		}
		
		mValue = alloc_empty_object ();
		alloc_field (mValue, id.bitsPerSample, alloc_int (bitsPerSample));
		alloc_field (mValue, id.channels, alloc_int (channels));
		alloc_field (mValue, id.handle, handleValue);
		alloc_field (mValue, id.sourceData, sourceData != NULL ? sourceData->mValue : alloc_null ());
		alloc_field (mValue, id.data, data->mValue);
		alloc_field (mValue, id.sampleRate, alloc_int (sampleRate));
		return mValue;
		
	}
	
	
}