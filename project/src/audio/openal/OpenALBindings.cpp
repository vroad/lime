#include <audio/openal/OpenALBindings.h>
#include <audio/openal/ALBuffer.h>
#include <audio/openal/ALSource.h>
#include <audio/openal/ALCContextWrapper.h>
#include <audio/openal/ALCDeviceWrapper.h>

//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIExt.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <utils/ArrayBufferView.h>
#include <utils/Kinds.h>
#include <utils/PointerWrapper.h>
#include <utils/HxVector.h>
#include <memory>
#include <vector>

namespace lime {
	
	std::unique_ptr<ALCContextWrapper, decltype(&release_ALCContextWrapper)> currentContext (NULL, release_ALCContextWrapper);
	
	std::vector<ALuint> getRawBuffers (value inBuffers) {
		
		ALuint size = val_array_size (inBuffers);
		std::vector<ALuint> buffers (size);
		
		if (size == 0) {
			
			return buffers;
			
		}
		
		for (int i = 0; i < size; i++) {
			
			ALBuffer* buffer = val_to_ALBuffer (val_array_i (inBuffers, i));
			buffers[i] = buffer != NULL ? buffer->buffer : 0;
			
		}
		
		return buffers;
		
	}
	
	
	std::vector<ALuint> getRawSources (value inSources) {
		
		ALuint size = val_array_size (inSources);
		std::vector<ALuint> sources (size);
		
		if (size == 0) {
			
			return sources;
			
		}
		
		for (int i = 0; i < size; i++) {
			
			ALSource* source = val_to_ALSource (val_array_i (inSources, i));
			sources[i] = source != NULL ? source->source : 0;
			
		}
		
		return sources;
		
	}
	
	
	void alBufferData_wrap (ALBuffer* buffer, int format, ArrayBufferView* data, int size, int freq) {
		
		alBufferData (buffer->buffer, format, data ? data->Data () : NULL, data ? data->ByteLength () : 0, freq);
		
	}
	
	
	void alBuffer3f_wrap (ALBuffer* buffer, int param, float value1, float value2, float value3) {
		
		alBuffer3f (buffer->buffer, param, value1, value2, value3);
		
	}
	
	
	void alBuffer3i_wrap (ALBuffer* buffer, int param, int value1, int value2, int value3) {
		
		alBuffer3i (buffer->buffer, param, value1, value2, value3);
		
	}
	
	
	void alBufferf_wrap (ALBuffer* buffer, int param, float value) {
		
		alBufferf (buffer->buffer, param, value);
		
	}
	
	
	void alBufferfv_wrap (ALBuffer* buffer, int param, const HxVector<float>& values) {
		
		alBufferfv (buffer->buffer, param, values.Data ());
		
	}
	
	void alBufferiv_wrap (ALBuffer* buffer, int param, const HxVector<int>& values) {
		
		alBufferiv (buffer->buffer, param, values.Data ());
		
	}
	
	
	void alBufferi_wrap (ALBuffer* buffer, int param, int value) {
		
		alBufferi (buffer->buffer, param, value);
		
	}
	
	
	void alDeleteBuffer_wrap (value buffer) {
		
		ALBuffer* buf = val_to_ALBuffer (buffer);
		if (buf != 0) {
			
			alDeleteBuffers (1, &buf->buffer);
			free_abstract (buffer);
			
		}
		
	}
	
	
	void alDeleteBuffers_wrap (value buffers) {
		
		if (val_is_null (buffers)) {
			
			return;
			
		}
		
		int size = val_array_size (buffers);
		for (int i = 0; i < size; i++) {
			
			value val = val_array_i (buffers, i);
			ALBuffer* buffer = val_to_ALBuffer (val);
			
			if (buffer != 0) {
				
				alDeleteBuffers ((ALuint)1, &buffer->buffer);
				
			}
			
		}
		
	}
	
	
	void alDeleteSource_wrap (value source) {
		
		ALSource* src = val_to_ALSource (source);
		
		if (src != 0) {
			
			alDeleteSources((ALuint)1, &src->source);
			free_abstract (source);
			
		}
		
	}
	
	
	void alDeleteSources_wrap (value sources) {
		
		if (val_is_null (sources)) {
			
			return;
			
		}
		
		int size = val_array_size (sources);
		for (int i = 0; i < size; i++) {
			
			value source = val_array_i (sources, i);
			ALSource* src = val_to_ALSource (source);
			
			if (source != 0) {
				
				alDeleteBuffers (1, &src->source);
				
			}
			
			free_abstract (source);
			
		}
		
	}
	
	
	ALBuffer* alGenBuffer_wrap (ALCContextWrapper* wrapper) {
		
		ALuint buffer;
		alGenBuffers ((ALuint)1, &buffer);
		return new ALBuffer (wrapper, buffer);
		
	}
	
	
	value alGenBuffers_wrap (ALCContextWrapper* wrapper, int n) {
		
		if (n <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<ALuint> buffers (n);
		alGenBuffers (n, &buffers[0]);
		
		value result = alloc_array (n);
		
		for (int i = 0; i < n; i++) {
			
			ALBuffer* buf = new ALBuffer (wrapper, buffers[i]);
			val_array_set_i (result, i, ALBuffer_to_val (buf));
			
		}
		
		return result;
		
	}
	
	
	ALSource* alGenSource_wrap (ALCContextWrapper* wrapper) {
		
		ALuint source;
		alGenSources ((ALuint)1, &source);
		return new ALSource (wrapper, source);
		
	}
	
	
	value alGenSources_wrap (ALCContextWrapper* wrapper, int n) {

		if (n <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALuint> sources (n);
		alGenSources (n, &sources[0]);
		
		value result = alloc_array (n);
		
		for (int i = 0; i < n; i++) {
			
			ALSource* src = new ALSource (wrapper, sources[i]);
			val_array_set_i (result, i, ALSource_to_val (src));
			
		}
		
		return result;
		
	}
	
	
	value alGetBooleanv_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALboolean> values (count);
		alGetBooleanv (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtBool);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_bool (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetBuffer3f_wrap (ALBuffer* buffer, int param) {
		
		ALfloat val1, val2, val3;
		
		alGetBuffer3f (buffer->buffer, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtFloat);
		val_array_set_i (result, 0, alloc_float (val1));
		val_array_set_i (result, 1, alloc_float (val2));
		val_array_set_i (result, 2, alloc_float (val3));
		return result;
		
	}
	
	
	value alGetBuffer3i_wrap (ALBuffer* buffer, int param) {
		
		ALint val1, val2, val3;
		
		alGetBuffer3i (buffer->buffer, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtInt);
		val_array_set_i (result, 0, alloc_int(val1));
		val_array_set_i (result, 1, alloc_int(val2));
		val_array_set_i (result, 2, alloc_int(val3));
		return result;
		
	}
	
	
	float alGetBufferf_wrap (ALBuffer* buffer, int param) {
		
		ALfloat data;
		alGetBufferf (buffer->buffer, param, &data);
		return data;
		
	}
	
	
	value alGetBufferfv_wrap (ALBuffer* buffer, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetBufferfv (buffer->buffer, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; ++i) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGetBufferi_wrap (ALBuffer* buffer, int param) {
		
		ALint data;
		alGetBufferi (buffer->buffer, param, &data);
		return data;
		
	}
	
	
	value alGetBufferiv_wrap (ALBuffer* buffer, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetBufferiv (buffer->buffer, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtInt);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetDoublev_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALdouble> values (count);
		alGetDoublev (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetFloatv_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetFloatv (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetIntegerv_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetIntegerv (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtInt);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetListener3f_wrap (int param) {
		
		ALfloat val1, val2, val3;
		
		alGetListener3f (param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtFloat);
		val_array_set_i (result, 0, alloc_float (val1));
		val_array_set_i (result, 1, alloc_float (val2));
		val_array_set_i (result, 2, alloc_float (val3));
		return result;
		
	}
	
	
	value alGetListener3i_wrap (int param) {
		
		ALint val1, val2, val3;
		
		alGetListener3i (param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtInt);
		val_array_set_i (result, 0, alloc_int (val1));
		val_array_set_i (result, 1, alloc_int (val2));
		val_array_set_i (result, 2, alloc_int (val3));
		return result;
		
	}
	
	
	float alGetListenerf_wrap (int param) {
		
		ALfloat data;
		alGetListenerf (param, &data);
		return data;
		
	}
	
	
	value alGetListenerfv_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetListenerfv (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGetListeneri_wrap (int param) {
		
		ALint data;
		alGetListeneri (param, &data);
		return data;
		
	}
	
	
	value alGetListeneriv_wrap (int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetListeneriv (param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtInt);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	value alGetSource3f_wrap (ALSource* source, int param) {
		
		ALfloat val1, val2, val3;
		
		alGetSource3f (source->source, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtFloat);
		val_array_set_i (result, 0, alloc_float (val1));
		val_array_set_i (result, 1, alloc_float (val2));
		val_array_set_i (result, 2, alloc_float (val3));
		return result;
		
	}
	
	
	value alGetSource3i_wrap (ALSource* source, int param) {
		
		ALint val1, val2, val3;
		
		alGetSource3i (source->source, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtInt);
		val_array_set_i (result, 1, alloc_int (val1));
		val_array_set_i (result, 2, alloc_int (val2));
		val_array_set_i (result, 3, alloc_int (val3));
		return result;
		
	}
	
	
	float alGetSourcef_wrap (ALSource* source, int param) {
		
		ALfloat data;
		alGetSourcef (source->source, param, &data);
		return data;
		
	}
	
	
	value alGetSourcefv_wrap (ALSource* source, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetSourcefv (source->source, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGetSourcei_wrap (ALSource* source, int param) {
		
		ALint data;
		alGetSourcei (source->source, param, &data);
		return data;
		
	}
	
	
	value alGetSourceiv_wrap (ALSource* source, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetSourceiv (source->source, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtInt);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	bool alIsBuffer_wrap (ALBuffer* buffer) {
		
		return alIsBuffer (buffer->buffer);
		
	}
	
	
	bool alIsSource_wrap (ALSource* source) {
		
		return alIsSource (source->source);
		
	}
	
	
	void alListenerfv_wrap (int param, const HxVector<float>& values) {
		
		alListenerfv (param, values.Data ());
		
	}
	
	
	void alListeneriv_wrap (int param, const HxVector<int>& values) {
		
		alListeneriv (param, values.Data ());
		
	}
	
	
	void alSource3f_wrap (ALSource* source, int param, float value1, float value2, float value3) {
		
		alSource3f (source->source, param, value1, value2, value3);
		
	}
	
	
	void alSource3i_wrap (ALSource* source, int param, int value1, int value2, int value3) {
		
		alSource3i (source->source, param, value1, value2, value3);
		
	}
	
	
	void alSourceBuffer (ALSource* source, value inBuffer) {
		
		ALBuffer* buffer = val_to_ALBuffer (inBuffer);
		alSourcei (source->source, AL_BUFFER, buffer->buffer);
		source->SetBuffer (inBuffer);
		
	}
	
	
	void alSourcePause_wrap (ALSource* source) {
		
		alSourcePause (source->source);
		
	}
	
	
	void alSourcePausev_wrap (value inSources) {
		
		std::vector<ALuint> sources = getRawSources (inSources);
		
		if (sources.size ()) {
			
			alSourcePausev (sources.size (), &sources[0]);
			
		}
		
	}
	
	
	void alSourcePlay_wrap (ALSource* source) {
		
		alSourcePlay (source->source);
		
	}
	
	
	void alSourcePlayv_wrap (value inSources) {
		
		std::vector<ALuint> sources = getRawSources (inSources);
		
		if (sources.size ()) {
			
			alSourcePlayv (sources.size (), &sources[0]);
			
		}
		
	}
	
	
	void alSourceQueueBuffers_wrap (ALSource* source, int nb, value inBuffers) {
		
		int size = val_array_size (inBuffers);
		
		if (size == 0) {
			
			return;
			
		}
		
		std::vector<ALuint> rawBuffers (size);
		
		for (int i = 0; i < size; i++) {
			
			value val = val_array_i (inBuffers, i);
			ALBuffer* buffer = val_to_ALBuffer (val);
			
			if (buffer != NULL) {
				
				rawBuffers[i] = buffer != NULL ? buffer->buffer : 0;
				source->AddQueuedBuffer (val);
				
			} else {
				
				rawBuffers[i] = 0;
				
			}
			
		}
		
		if (size) {
			
			alSourceQueueBuffers (source->source, nb, &rawBuffers[0]);
			
		}
		
	}
	
	
	void alSourceRewind_wrap (ALSource* source) {
		
		alSourceRewind (source->source);
		
	}
	
	
	void alSourceRewindv_wrap (value inSources) {
		
		std::vector<ALuint> sources = getRawSources (inSources);
		
		if (sources.size ()) {
			
			alSourceRewindv (sources.size (), &sources[0]);
			
		}
		
	}
	
	
	void alSourceStop_wrap (ALSource* source) {
		
		alSourceStop (source->source);
		
	}
	
	
	void alSourceStopv_wrap (value inSources) {
		
		std::vector<ALuint> sources = getRawSources (inSources);
		
		if (sources.size ()) {
			
			alSourceStopv (sources.size (), &sources[0]);
			
		}
		
	}
	
	
	value alSourceUnqueueBuffers_wrap (ALSource* source, int nb) {
		
		if (nb <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<ALuint> rawBuffers (nb);
		alSourceUnqueueBuffers (source->source, nb, &rawBuffers[0]);
		
		value result = alloc_array (nb);
		
		for (int i = 0; i < nb; i++) {
			
			val_array_set_i (result, i, source->RemoveQueuedBufferById (rawBuffers[i]));
			
		}
		
		return result;
		
	}
	
	
	void alSourcef_wrap (ALSource* source, int param, float value) {
		
		alSourcef (source->source, param, value);
		
	}
	
	
	void alSourcefv_wrap (ALSource* source, int param, const HxVector<float>& values) {
		
		alSourcefv (source->source, param, values.Data ());
		
	}
	
	
	void alSourcei_wrap (ALSource* source, int param, int value) {
		
		alSourcei (source->source, param, value);
		
	}
	
	
	void alSourceiv_wrap (ALSource* source, int param, const HxVector<int>& values) {
		
		alSourceiv (source->source, param, values.Data ());
		
	}
	
	
	bool alcCloseDevice_wrap (value device) {
		
		ALCDeviceWrapper* wrapper = val_to_ALCDeviceWrapper (device);
		
		if (wrapper) {
			
			wrapper->Release ();
			free_abstract (device);
			
		}
		
		return true;
		
	}
	
	
	ALCContextWrapper* alcCreateContext_wrap (ALCDeviceWrapper* deviceWrapper, const HxVector<int>& attrList) {
		
		ALCcontext* alcContext = alcCreateContext (deviceWrapper->alcDevice, attrList.Data ());
		return alcContext != NULL ? new ALCContextWrapper (alcContext, deviceWrapper) : NULL;
		
	}
	
	
	void alcDestroyContext_wrap (value context) {
		
		ALCContextWrapper* contextWrap = val_to_ALCContextWrapper (context);
		contextWrap->Dispose ();
		contextWrap->Release ();
		free_abstract (context);
		
	}
	
	
	void alcDevicePauseSOFT_wrap (ALCDeviceWrapper* wrapper) {
		
		#ifdef LIME_OPENALSOFT
		alcDevicePauseSOFT (wrapper->alcDevice);
		#endif
		
	}
	
	
	void alcDeviceResumeSOFT_wrap (ALCDeviceWrapper* wrapper) {
		
		#ifdef LIME_OPENALSOFT
		alcDeviceResumeSOFT (wrapper->alcDevice);
		#endif
		
	}
	
	
	int alcGetError_wrap (ALCDeviceWrapper* wrapper) {
		
		return alcGetError (wrapper->alcDevice);
		
	}
	
	
	value alcGetIntegerv_wrap (ALCDeviceWrapper* wrapper, int param, int size) {
		
		if (size <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<ALCint> values (size);
		alcGetIntegerv (wrapper->alcDevice, param, size, &values[0]);
		
		value result = alloc_array_type_wrap (size, valtInt);
		
		for (int i = 0; i < size; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	const char* alcGetString_wrap (ALCDeviceWrapper* wrapper, int param) {
		
		return alcGetString (wrapper->alcDevice, param);
		
	}
	
	
	bool alcMakeContextCurrent_wrap (ALCContextWrapper_Nullable* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		bool result = alcMakeContextCurrent (alcContext);
		
		if (result && currentContext.get () != contextWrap) {
			
			currentContext.reset (contextWrap);
			
			if (currentContext) {
				
				currentContext->AddRef ();
				
			}
			
		}
		
		return result;
		
	}
	
	
	ALCDeviceWrapper* alcOpenDevice_wrap (const char* deviceName) {
		
		ALCDeviceWrapper* wrapper = ALCDeviceWrapper::Create (deviceName);
		return wrapper;
		
	}
	
	
	void alcProcessContext_wrap (ALCContextWrapper* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		return alcProcessContext (alcContext);
		
	}
	
	
	void alcSuspendContext_wrap (ALCContextWrapper* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		return alcSuspendContext (alcContext);
		
	}
	
	
}


extern "C" int lime_openal_register_prims () {
	
	return 0;
	
}
