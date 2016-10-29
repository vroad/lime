#include <audio/openal/ALCDeviceWrapper.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>
#include <assert.h>

namespace lime {
	
	
	ALCDeviceWrapper::ALCDeviceWrapper () {
		
		alcDevice = NULL;
		refCount = 1;
		
	}
	
	
	bool ALCDeviceWrapper::Init (const char* deviceName) {
		
		alcDevice = alcOpenDevice (deviceName);
		
		if (alcDevice == NULL) {
			
			return false;
			
		}
		
		return true;
		
	}
	
	
	ALCDeviceWrapper* ALCDeviceWrapper::Create (const char* deviceName) {
		
		ALCDeviceWrapper* wrapper = new ALCDeviceWrapper();
		
		if (!wrapper->Init (deviceName)) {
			
			delete wrapper;
			return NULL;
			
		}
		
		return wrapper;
		
	}
	
	
	ALCDeviceWrapper::~ALCDeviceWrapper () {
		
		alcCloseDevice (alcDevice);
		
	}
	
	
	void ALCDeviceWrapper::AddRef () {
		
		refCount++;
		
	}
	
	
	void ALCDeviceWrapper::Release () {
		
		assert (refCount >= 1);
		refCount--;
		
		if (refCount == 0) {
			
			delete this;
			
		}
		
	}
	
	
	void gc_ALCDevice (value inData) {
		
		ALCDeviceWrapper *wrapper = (ALCDeviceWrapper*)val_data (inData);
		wrapper->Release ();
		free_abstract (inData);
		
	}
	
	
	ALCDeviceWrapper* val_to_ALCDeviceWrapper (value inHandle) {
		
		return lime_abstract_to_pointer<ALCDeviceWrapper> (inHandle, Kinds::Get ()->ALCDeviceWrapper);
		
	}
	
	
	value ALCDeviceWrapper_to_val (ALCDeviceWrapper* inInstance) {
		
		return CFFIPointer (inInstance, gc_ALCDevice, Kinds::Get ()->ALCDeviceWrapper);
		
	}
	
	
}