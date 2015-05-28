#include <audio/AudioBuffer.h>


namespace lime {
	
	
	static int id_bitsPerSample;
	static int id_channels;
	static int id_handle;
	static int id_sourceData;
	static int id_data;
	static int id_sampleRate;
	static bool init = false;
	
	
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
		
		if (!init) {
			
			id_bitsPerSample = val_id ("bitsPerSample");
			id_channels = val_id ("channels");
			id_handle = val_id ("handle");
			id_sourceData = val_id ("sourceData");
			id_data = val_id ("data");
			id_sampleRate = val_id ("sampleRate");
			init = true;
			
		}
		
		mValue = alloc_empty_object ();
		alloc_field (mValue, id_bitsPerSample, alloc_int (bitsPerSample));
		alloc_field (mValue, id_channels, alloc_int (channels));
		alloc_field (mValue, id_handle, handle != NULL ? alloc_float ((intptr_t)handle) : alloc_null ());
		alloc_field (mValue, id_sourceData, sourceData != NULL ? sourceData->mValue : alloc_null ());
		alloc_field (mValue, id_data, data->mValue);
		alloc_field (mValue, id_sampleRate, alloc_int (sampleRate));
		return mValue;
		
	}
	
	
}