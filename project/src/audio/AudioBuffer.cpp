#include <audio/AudioBuffer.h>
#include <utils/PointerWrapper.h>
#include <utils/ThreadLocalStorage.h>
#include <utils/Kinds.h>

namespace lime {
	
	static ThreadLocalStorage<AudioBufferId> stringId;
	
	AudioBufferId GetAudioBufferId () {
		
		AudioBufferId id = stringId.Get ();
		if (!id.init) {
			
			id.bitsPerSample = val_id ("bitsPerSample");
			id.channels = val_id ("channels");
			id.handle = val_id ("handle");
			id.sourceData = val_id ("sourceData");
			id.data = val_id ("data");
			id.sampleRate = val_id ("sampleRate");
			id.length = val_id ("length");
			id.init = true;
			stringId.Set (id);
			
		}
		
		return id;
		
	}
	
	template <>
	value WrapPointer<AudioBuffer> (AudioBuffer *pointer) {
		
		return WrapPointerInternal<AudioBuffer> (pointer, GetKinds ().AudioBuffer);
		
	}

	template <>
	value WrapPointer<AudioStream> (AudioStream *pointer) {
		
		AudioBufferId id = GetAudioBufferId ();
		return WrapPointerInternal<AudioStream> (pointer, GetKinds ().AudioStream);
		
	}

	AudioBuffer::AudioBuffer () {
		
		bitsPerSample = 0;
		channels = 0;
		handle = NULL;
		sourceData = NULL;
		data = NULL;
		sampleRate = 0;
		length = 0;
		
	}
	
	
	AudioBuffer::~AudioBuffer () {
		
		delete sourceData;
		delete data;
		
	}
	
	
	value AudioBuffer::Value () {
		
		
		value handleValue;
		if (handle != NULL) {
			
			handleValue = WrapPointerWithGC<AudioStream> (handle);
			
		} else {
			
			handleValue = alloc_null ();
			
		}
		
		mValue = alloc_empty_object ();
		AudioBufferId id = GetAudioBufferId ();
		alloc_field (mValue, id.bitsPerSample, alloc_int (bitsPerSample));
		alloc_field (mValue, id.channels, alloc_int (channels));
		alloc_field (mValue, id.handle, handleValue);
		alloc_field (mValue, id.sourceData, sourceData != NULL ? sourceData->Value () : alloc_null ());
		alloc_field (mValue, id.data, data != NULL ? data->Value () : alloc_null ());
		alloc_field (mValue, id.sampleRate, alloc_int (sampleRate));
		alloc_field (mValue, id.length, alloc_int (length));
		return mValue;
		
	}
	
	
}