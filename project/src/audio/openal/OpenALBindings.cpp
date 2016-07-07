#include <audio/openal/OpenALBindings.h>

//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIExt.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <utils/ArrayBufferView.h>
#include <utils/Kinds.h>
#include <utils/PointerWrapper.h>
#include <utils/HxVector.h>
#include <vector>

namespace lime {
	
	
	void gc_alc_device (value device) {
		
		ALCdevice* alcDevice = (ALCdevice*)val_data (device);
		alcCloseDevice (alcDevice);
		free_abstract (device);
		
	}
	
	void alBufferData_wrap (int buffer, int format, ArrayBufferView* data, int size, int freq) {
		
		alBufferData (buffer, format, data ? data->Data () : NULL, data ? data->ByteLength () : 0, freq);
		
	}
	
	void alBufferfv_wrap (int buffer, int param, const HxVector<float>& values) {
		
		alBufferfv (buffer, param, values.Data ());
		
	}
	
	void alBufferiv_wrap (int buffer, int param, const HxVector<int>& values) {
		
		alBufferiv (buffer, param, values.Data ());
		
	}
	
	
	void alDeleteBuffer_wrap (int buffer) {
		
		ALuint data = buffer;
		alDeleteBuffers ((ALuint)1, &data);
		
	}
	
	
	void alDeleteBuffers_wrap (const HxVector<int>& buffers) {
		
		alDeleteBuffers (buffers.Length (), (const ALuint*)buffers.Data ());
		
	}
	
	
	void alDeleteSource_wrap (int source) {
		
		ALuint data = source;
		alDeleteSources(1, &data);
		
	}
	
	
	void alDeleteSources_wrap (const HxVector<int>& sources) {
		
		alDeleteSources (sources.Length (), (const ALuint*)sources.Data ());
		
	}
	
	
	int alGenBuffer_wrap () {
		
		ALuint buffer;
		alGenBuffers ((ALuint)1, &buffer);
		return buffer;
		
	}
	
	
	value alGenBuffers_wrap (int n) {

		if (n <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALuint> buffers (n);
		alGenBuffers (n, &buffers[0]);
		
		value result = alloc_array_type_wrap (n, valtInt);
		
		for (int i = 0; i < n; i++) {
			
			val_array_set_i (result, i, alloc_int (buffers[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGenSource_wrap () {
		
		ALuint source;
		alGenSources ((ALuint)1, &source);
		return source;
		
	}
	
	
	value alGenSources_wrap (int n) {

		if (n <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALuint> sources (n);
		alGenSources (n, &sources[0]);
		
		value result = alloc_array_type_wrap (n, valtInt);
		
		for (int i = 0; i < n; i++) {
			
			val_array_set_i (result, i, alloc_int (sources[i]));
			
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
	
	
	value alGetBuffer3f_wrap (int buffer, int param) {
		
		ALfloat val1, val2, val3;
		
		alGetBuffer3f (buffer, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtFloat);
		val_array_set_i (result, 0, alloc_float (val1));
		val_array_set_i (result, 1, alloc_float (val2));
		val_array_set_i (result, 2, alloc_float (val3));
		return result;
		
	}
	
	
	value alGetBuffer3i_wrap (int buffer, int param) {
		
		ALint val1, val2, val3;
		
		alGetBuffer3i (buffer, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtInt);
		val_array_set_i (result, 0, alloc_int(val1));
		val_array_set_i (result, 1, alloc_int(val2));
		val_array_set_i (result, 2, alloc_int(val3));
		return result;
		
	}
	
	
	float alGetBufferf_wrap (int buffer, int param) {
		
		ALfloat data;
		alGetBufferf (buffer, param, &data);
		return data;
		
	}
	
	
	value alGetBufferfv_wrap (int buffer, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetBufferfv (buffer, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; ++i) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGetBufferi_wrap (int buffer, int param) {
		
		ALint data;
		alGetBufferi (buffer, param, &data);
		return data;
		
	}
	
	
	value alGetBufferiv_wrap (int buffer, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetBufferiv (buffer, param, &values[0]);
		
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
	
	
	value alGetSource3f_wrap (int source, int param) {
		
		ALfloat val1, val2, val3;
		
		alGetSource3f (source, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtFloat);
		val_array_set_i (result, 0, alloc_float (val1));
		val_array_set_i (result, 1, alloc_float (val2));
		val_array_set_i (result, 2, alloc_float (val3));
		return result;
		
	}
	
	
	value alGetSource3i_wrap (int source, int param) {
		
		ALint val1, val2, val3;
		
		alGetSource3i (source, param, &val1, &val2, &val3);
		
		value result = alloc_array_type_wrap (3, valtInt);
		val_array_set_i (result, 1, alloc_int (val1));
		val_array_set_i (result, 2, alloc_int (val2));
		val_array_set_i (result, 3, alloc_int (val3));
		return result;
		
	}
	
	
	float alGetSourcef_wrap (int source, int param) {
		
		ALfloat data;
		alGetSourcef (source, param, &data);
		return data;
		
	}
	
	
	value alGetSourcefv_wrap (int source, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALfloat> values (count);
		alGetSourcefv (source, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtFloat);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_float (values[i]));
			
		}
		
		return result;
		
	}
	
	
	int alGetSourcei_wrap (int source, int param) {
		
		ALint data;
		alGetSourcei (source, param, &data);
		return data;
		
	}
	
	
	value alGetSourceiv_wrap (int source, int param, int count) {

		if (count <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALint> values (count);
		alGetSourceiv (source, param, &values[0]);
		
		value result = alloc_array_type_wrap (count, valtInt);
		
		for (int i = 0; i < count; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	void alListenerfv_wrap (int param, const HxVector<float>& values) {
		
		alListenerfv (param, values.Data ());
		
	}
	
	
	void alListeneriv_wrap (int param, const HxVector<int>& values) {
		
		alListeneriv (param, values.Data ());
		
	}
	
	
	void alSourcePausev_wrap (int n, const HxVector<int>& sources) {
		
		alSourcePausev (n, (const ALuint*)sources.Data ());
		
	}
	
	
	void alSourcePlayv_wrap (int n, const HxVector<int>& sources) {
		
		alSourcePlayv (n, (const ALuint*)sources.Data ());
		
	}
	
	
	void alSourceQueueBuffers_wrap (int source, int nb, const HxVector<int>& buffers) {
			
		alSourceQueueBuffers (source, nb, (const ALuint*)buffers.Data ());
		
	}
	
	
	void alSourceRewindv_wrap (int n, const HxVector<int>& sources) {
			
		alSourceRewindv (n, (const ALuint*)sources.Data ());
		
	}
	
	
	void alSourceStopv_wrap (int n, const HxVector<int>& sources) {
		
		alSourceStopv (n, (const ALuint*)sources.Data ());
		
	}
	
	
	value alSourceUnqueueBuffers_wrap (int source, int nb) {

		if (nb <= 0) {

			return alloc_null ();

		}
		
		std::vector<ALuint> buffers (nb);
		alSourceUnqueueBuffers (source, nb, &buffers[0]);
		
		value result = alloc_array_type_wrap (nb, valtInt);
		
		for (int i = 0; i < nb; i++) {
			
			val_array_set_i (result, i, alloc_int (buffers[i]));
			
		}
		
		return result;
		
	}
	
	
	void alSourcefv_wrap (int source, int param, const HxVector<float>& values) {
		
		alSourcefv (source, param, values.Data ());
		
	}
	
	
	void alSourceiv_wrap (int source, int param, const HxVector<int>& values) {
		
		alSourceiv (source, param, values.Data ());
		
	}
	
	
	bool alcCloseDevice_wrap (value device) {
		
		ALCdevice* alcDevice = val_to_ALCdevice (device);
		bool result = alcCloseDevice (alcDevice);
		free_abstract (device);
		return result;
		
	}
	
	
	ALCContextWrapper* alcCreateContext_wrap (value device, const HxVector<int>& attrList) {
		
		ALCdevice* alcDevice = val_to_ALCdevice (device);
		ALCcontext* alcContext = alcCreateContext (alcDevice, attrList.Data ());
		return alcContext != NULL ? new ALCContextWrapper (alcContext, device) : NULL;
		
	}
	
	
	void alcDestroyContext_wrap (value context) {
		
		ALCContextWrapper* contextWrap = val_to_ALCContextWrapper (context);
		delete contextWrap;
		free_abstract (context);
		
	}
	
	
	value alcGetContextsDevice_wrap (ALCContextWrapper* contextWrap) {
		
		return contextWrap->alcDevice->get ();
		
	}
	
	
	value alcGetIntegerv_wrap (ALCdevice* alcDevice, int param, int size) {
		
		if (size <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<ALCint> values (size);
		alcGetIntegerv (alcDevice, param, size, &values[0]);
		
		value result = alloc_array_type_wrap (size, valtInt);
		
		for (int i = 0; i < size; i++) {
			
			val_array_set_i (result, i, alloc_int (values[i]));
			
		}
		
		return result;
		
	}
	
	
	bool alcMakeContextCurrent_wrap (ALCContextWrapper_Nullable* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		return alcMakeContextCurrent (alcContext);
		
	}
	
	
	void alcProcessContext_wrap (ALCContextWrapper* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		return alcProcessContext (alcContext);
		
	}
	
	
	void alcSuspendContext_wrap (ALCContextWrapper* contextWrap) {
		
		ALCcontext* alcContext = contextWrap != NULL ? contextWrap->alcContext : NULL;
		return alcSuspendContext (alcContext);
		
	}
	
	
	ALCdevice* val_to_ALCdevice (value inHandle) {
		
		return lime_abstract_to_pointer<ALCdevice> (inHandle, Kinds::Get ()->ALCdevice);
		
	}
	
	value ALCdevice_to_val (ALCdevice* inInstance) {
		
		return CFFIPointer (inInstance, gc_alc_device, Kinds::Get ()->ALCdevice);
		
	}
	
	
}


extern "C" int lime_openal_register_prims () {
	
	return 0;
	
}
