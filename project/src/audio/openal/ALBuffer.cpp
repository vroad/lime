#include <audio/openal/ALBuffer.h>
#include <audio/openal/ALCContextWrapper.h>
#include <utils/Kinds.h>
#include <assert.h>

namespace lime {
	
	
	ALBuffer::ALBuffer (ALCContextWrapper* contextWrapper, ALuint buffer) {
		
		this->contextWrapper = contextWrapper;
		this->buffer = buffer;
		this->contextWrapper->AddRef ();
		
	}
	
	
	ALBuffer::~ALBuffer () {
		
		// TODO: Support for multiple contexts
		if (!contextWrapper->disposed) {
			
			alDeleteBuffers (1, &buffer);
			
		}
		
		contextWrapper->Release ();
		
	}
	
	
	void gc_ALBuffer (value inHandle) {
		
		ALBuffer* buffer = (ALBuffer*)val_data (inHandle);
		delete buffer;
		
	}
	
	
	ALBuffer* val_to_ALBuffer (value inHandle) {
		
		return lime_abstract_to_pointer<ALBuffer> (inHandle, Kinds::Get ()->ALBuffer);
		
	}
	
	
	value ALBuffer_to_val (ALBuffer* inInstance) {
		
		return CFFIPointer (inInstance, gc_ALBuffer, Kinds::Get ()->ALBuffer);
		
	}
	
	
}