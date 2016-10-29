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


#include <utils/ArrayBufferView.h>
#include <utils/HxVector.h>


namespace lime {
	
	class ALBuffer;
	class ALSource;
	class ALCContextWrapper;
	class ALCDeviceWrapper;
	typedef ALCContextWrapper ALCContextWrapper_Nullable;
	
	void alBufferData_wrap (ALBuffer* buffer, int format, ArrayBufferView* data, int size, int freq);
	
	void alBuffer3f_wrap (ALBuffer* buffer, int param, float value1, float value2, float value3);
	
	void alBuffer3i_wrap (ALBuffer* buffer, int param, int value1, int value2, int value3);
	
	void alBufferf_wrap (ALBuffer* buffer, int param, float value);
	
	void alBufferfv_wrap (ALBuffer* buffer, int param, const HxVector<float>& values);
	
	void alBufferi_wrap (ALBuffer* buffer, int param, int value);
	
	void alBufferiv_wrap (ALBuffer* buffer, int param, const HxVector<int>& values);
	
	void alDeleteBuffer_wrap (value buffer);
	
	void alDeleteBuffers_wrap (value buffers);
	
	void alDeleteSource_wrap (value source);
	
	void alDeleteSources_wrap (value sources);
	
	value alGetBooleanv_wrap (int param, int count);
	
	ALBuffer* alGenBuffer_wrap (ALCContextWrapper* wrapper);
	
	value alGenBuffers_wrap (ALCContextWrapper* wrapper, int n);
	
	ALSource* alGenSource_wrap (ALCContextWrapper* wrapper);
	
	value alGenSources_wrap (ALCContextWrapper* wrapper, int n);
	
	value alGetBuffer3f_wrap (ALBuffer* buffer, int param);
	
	value alGetBuffer3i_wrap (ALBuffer* buffer, int param);
	
	float alGetBufferf_wrap (ALBuffer* buffer, int param);
	
	value alGetBufferfv_wrap (ALBuffer* buffer, int param, int count);
	
	int alGetBufferi_wrap (ALBuffer* buffer, int param);
	
	value alGetBufferiv_wrap (ALBuffer* buffer, int param, int count);
	
	value alGetDoublev_wrap (int param, int count);
	
	value alGetFloatv_wrap (int param, int count);
	
	value alGetIntegerv_wrap (int param, int count);
	
	value alGetListener3f_wrap (int param);
	
	value alGetListener3i_wrap (int param);
	
	float alGetListenerf_wrap (int param);
	
	value alGetListenerfv_wrap (int param, int count);
	
	int alGetListeneri_wrap (int param);
	
	value alGetListeneriv_wrap (int param, int count);
	
	value alGetSource3f_wrap (ALSource* source, int param);
	
	value alGetSource3i_wrap (ALSource* source, int param);
	
	float alGetSourcef_wrap (ALSource* source, int param);
	
	value alGetSourcefv_wrap (ALSource* source, int param, int count);
	
	int alGetSourcei_wrap (ALSource* source, int param);
	
	value alGetSourceiv_wrap (ALSource* source, int param, int count);
	
	bool alIsBuffer_wrap (ALBuffer* buffer);
	
	bool alIsSource_wrap (ALSource* source);
	
	void alListenerfv_wrap (int param, const HxVector<float>& values);
	
	void alListeneriv_wrap (int param, const HxVector<int>& values);
	
	void alSource3f_wrap (ALSource* source, int param, float value1, float value2, float value3);
	
	void alSource3i_wrap (ALSource* source, int param, int value1, int value2, int value3);
	
	void alSourceBuffer (ALSource* source, value inBuffer);
	
	void alSourcePause_wrap (ALSource* source);
	
	void alSourcePausev_wrap (value inSources);
	
	void alSourcePlay_wrap (ALSource* source);
	
	void alSourcePlayv_wrap (value inSources);
	
	void alSourceQueueBuffers_wrap (ALSource* source, int nb, value inBuffers);
	
	void alSourceRewind_wrap (ALSource* source);
	
	void alSourceRewindv_wrap (value inSources);
	
	void alSourceStop_wrap (ALSource* source);
	
	void alSourceStopv_wrap (value inSources);
	
	value alSourceUnqueueBuffers_wrap (ALSource* source, int nb);
	
	void alSourcef_wrap (ALSource* source, int param, float value);
	
	void alSourcefv_wrap (ALSource* source, int param, const HxVector<float>& values);
	
	void alSourcei_wrap (ALSource* source, int param, int value);
	
	void alSourceiv_wrap (ALSource* source, int param, const HxVector<int>& values);
	
	bool alcCloseDevice_wrap (value device);
	
	ALCContextWrapper* alcCreateContext_wrap (ALCDeviceWrapper* deviceWrapper, const HxVector<int>& attrList);
	
	void alcDestroyContext_wrap (value context);
	
	void alcDevicePauseSOFT_wrap (ALCDeviceWrapper* wrapper);
	
	void alcDeviceResumeSOFT_wrap (ALCDeviceWrapper* wrapper);
	
	int alcGetError_wrap (ALCDeviceWrapper* wrapper);
	
	value alcGetIntegerv_wrap (ALCDeviceWrapper* wrapper, int param, int size);
	
	const char* alcGetString_wrap (ALCDeviceWrapper* wrapper, int param);
	
	bool alcMakeContextCurrent_wrap (ALCContextWrapper_Nullable* contextWrap);
	
	ALCDeviceWrapper* alcOpenDevice_wrap (const char* deviceName);
	
	void alcProcessContext_wrap (ALCContextWrapper* contextWrap);
	
	void alcSuspendContext_wrap (ALCContextWrapper* contextWrap);
	
	
}


#endif