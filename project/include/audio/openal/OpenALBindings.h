#ifndef LIME_AUDIO_OPENAL_OPENAL_BINDINGS_H
#define LIME_AUDIO_OPENAL_OPENAL_BINDINGS_H


#if defined (IPHONE) || defined (TVOS) || (defined (HX_MACOS) && !defined (LIME_OPENALSOFT))
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include "AL/al.h"
#include "AL/alc.h"
#ifdef LIME_OPENALSOFT
#include "AL/alext.h"
#endif
#endif

#include <audio/openal/ALCContextWrapper.h>

#include <utils/ArrayBufferView.h>
#include <utils/HxVector.h>


namespace lime {
	
	
	void alBufferData_wrap (int buffer, int format, ArrayBufferView* data, int size, int freq);
	
	void alBufferfv_wrap (int buffer, int param, const HxVector<float>& values);
	
	void alBufferiv_wrap (int buffer, int param, const HxVector<int>& values);
	
	void alDeleteBuffer_wrap (int buffer);
	
	void alDeleteBuffers_wrap (const HxVector<int>& buffers);
	
	void alDeleteSource_wrap (int source);
	
	void alDeleteSources_wrap (const HxVector<int>& sources);
	
	value alGetBooleanv_wrap (int param, int count);
	
	int alGenBuffer_wrap ();
	
	value alGenBuffers_wrap (int n);
	
	int alGenSource_wrap ();
	
	value alGenSources_wrap (int n);
	
	value alGetBuffer3f_wrap (int buffer, int param);
	
	value alGetBuffer3i_wrap (int buffer, int param);
	
	float alGetBufferf_wrap (int buffer, int param);
	
	value alGetBufferfv_wrap (int buffer, int param, int count);
	
	int alGetBufferi_wrap (int buffer, int param);
	
	value alGetBufferiv_wrap (int buffer, int param, int count);
	
	value alGetDoublev_wrap (int param, int count);
	
	value alGetFloatv_wrap (int param, int count);
	
	value alGetIntegerv_wrap (int param, int count);
	
	value alGetListener3f_wrap (int param);
	
	value alGetListener3i_wrap (int param);
	
	float alGetListenerf_wrap (int param);
	
	value alGetListenerfv_wrap (int param, int count);
	
	int alGetListeneri_wrap (int param);
	
	value alGetListeneriv_wrap (int param, int count);
	
	value alGetSource3f_wrap (int source, int param);
	
	value alGetSource3i_wrap (int source, int param);
	
	float alGetSourcef_wrap (int source, int param);
	
	value alGetSourcefv_wrap (int source, int param, int count);
	
	int alGetSourcei_wrap (int source, int param);
	
	value alGetSourceiv_wrap (int source, int param, int count);
	
	void alListenerfv_wrap (int param, const HxVector<float>& values);
	
	void alListeneriv_wrap (int param, const HxVector<int>& values);
	
	void alSourcePausev_wrap (int n, const HxVector<int>& sources);
	
	void alSourcePlayv_wrap (int n, const HxVector<int>& sources);
	
	void alSourceQueueBuffers_wrap (int source, int nb, const HxVector<int>& buffers);
	
	void alSourceRewindv_wrap (int n, const HxVector<int>& sources);
	
	void alSourceStopv_wrap (int n, const HxVector<int>& sources);
	
	value alSourceUnqueueBuffers_wrap (int source, int nb);
	
	void alSourcefv_wrap (int source, int param, const HxVector<float>& values);
	
	void alSourceiv_wrap (int source, int param, const HxVector<int>& values);
	
	bool alcCloseDevice_wrap (value device);
	
	ALCContextWrapper* alcCreateContext_wrap (value device, const HxVector<int>& attrList);
	
	void alcDestroyContext_wrap (value context);
	
	value alcGetContextsDevice_wrap (ALCContextWrapper* contextWrap);
	
	value alcGetIntegerv_wrap (ALCdevice* alcDevice, int param, int size);
	
	bool alcMakeContextCurrent_wrap (ALCContextWrapper_Nullable* contextWrap);
	
	void alcProcessContext_wrap (ALCContextWrapper* contextWrap);
	
	void alcSuspendContext_wrap (ALCContextWrapper* contextWrap);
	
	
	ALCdevice* val_to_ALCdevice (value inHandle);
	
	value ALCdevice_to_val (ALCdevice* inInstance);
	
}


#endif