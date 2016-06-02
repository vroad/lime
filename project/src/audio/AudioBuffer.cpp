#include <audio/AudioBuffer.h>
#include <system/CFFIPointer.h>
#include <utils/PointerWrapper.h>
#include <utils/StringId.h>

namespace lime {
	
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
			
			handleValue = CFFIPointer (handle, lime_pointer_destroy<AudioStream>);
			
		} else {
			
			handleValue = alloc_null ();
			
		}
		
		mValue = alloc_empty_object ();
		StringId *id = StringId::Get ();
		alloc_field (mValue, id->bitsPerSample, alloc_int (bitsPerSample));
		alloc_field (mValue, id->channels, alloc_int (channels));
		alloc_field (mValue, id->handle, handleValue);
		alloc_field (mValue, id->sourceData, sourceData != NULL ? sourceData->Value () : alloc_null ());
		alloc_field (mValue, id->data, data != NULL ? data->Value () : alloc_null ());
		alloc_field (mValue, id->sampleRate, alloc_int (sampleRate));
		alloc_field (mValue, id->length, alloc_int (length));
		return mValue;
		
	}
	
	
}