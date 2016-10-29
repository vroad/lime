#include <audio/openal/ALCContextWrapper.h>
#include <audio/openal/ALCDeviceWrapper.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>
#include <assert.h>

namespace lime {
	
	
	ALCContextWrapper::ALCContextWrapper (ALCcontext* context, ALCDeviceWrapper* deviceWrapper) {
		
		this->alcContext = context;
		this->deviceWrapper = deviceWrapper;
		this->deviceWrapper->AddRef();
		refCount = 1;
		
	}
	
	
	ALCContextWrapper::~ALCContextWrapper () {
		
		ALCcontext* currentContext = alcGetCurrentContext();
		
		if (currentContext == this->alcContext) {
			
			alcMakeContextCurrent (NULL);
			
		}
		
		alcDestroyContext (alcContext);
		this->deviceWrapper->Release ();
		
	}
	
	
	void ALCContextWrapper::AddRef () {
		
		refCount++;
		
	}
	
	
	void ALCContextWrapper::Release () {
		
		assert (refCount >= 1);
		refCount--;
		
		if (refCount == 0) {
			
			delete this;
			
		}
		
	}
	
	
	void release_ALCContextWrapper (ALCContextWrapper* wrapper) {
		
		wrapper->Release ();
		
	}
	
	
	void gc_ALCContextWrapper (value inHandle) {
		
		ALCContextWrapper* wrapper = (ALCContextWrapper*)val_data (inHandle);
		wrapper->Release ();
		
	}
	
	
	ALCContextWrapper* val_to_ALCContextWrapper (value inHandle) {
		
		return lime_abstract_to_pointer<ALCContextWrapper> (inHandle, Kinds::Get ()->ALCContextWrapper);
		
	}
	
	
	value ALCContextWrapper_to_val (ALCContextWrapper* inInstance) {
		
		return CFFIPointer (inInstance, gc_ALCContextWrapper, Kinds::Get ()->ALCContextWrapper);
		
	}
	
	
}