#include <audio/AudioBuffer.h>
#include <system/CFFIPointer.h>
#include <utils/PointerWrapper.h>
#include <utils/StringId.h>

namespace lime {
	
	AudioBuffer::AudioBuffer () {
		
		bitsPerSample = 0;
		channels = 0;
		sampleRate = 0;
		mValue = 0;
		
	}
	
	
	AudioBuffer::~AudioBuffer () {
		
	}
	
	
	value AudioBuffer::Value () {
		
		if (mValue == 0 || val_is_null (mValue)) {
			
			mValue = alloc_empty_object ();
			
		}
		
		StringId *id = StringId::Get ();
		alloc_field (mValue, id->bitsPerSample, alloc_int (bitsPerSample));
		alloc_field (mValue, id->channels, alloc_int (channels));
		alloc_field (mValue, id->data, data.Value ());
		alloc_field (mValue, id->sampleRate, alloc_int (sampleRate));
		return mValue;
		
	}
	
	
}