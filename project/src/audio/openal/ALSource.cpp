#include <audio/openal/ALSource.h>
#include <audio/openal/ALBuffer.h>
#include <audio/openal/ALCContextWrapper.h>
#include <utils/Kinds.h>
#include <assert.h>

namespace lime {
	
	
	ALSource::ALSource (ALCContextWrapper* contextWrapper, ALuint source) {
		
		this->contextWrapper = contextWrapper;
		this->source = source;
		this->contextWrapper->AddRef ();
		bufferRef = NULL;
		
	}
	
	
	ALSource::~ALSource () {
		
		delete bufferRef;
		
		for (std::map<ALuint, AutoGCRoot*>::iterator it = queuedBuffers.begin (); it != queuedBuffers.end (); ++it) {
			
			delete it->second;
			
		}
		
		// TODO: Support deleting sources automatically
		// TODO: Support for multiple contexts
		//alDeleteSources (1, &source);
		this->contextWrapper->Release ();
		
	}
	
	
	void ALSource::SetBuffer (value buffer) {
		
		if (bufferRef) {
			
			bufferRef->set (buffer);
			
		} else {
			
			bufferRef = new AutoGCRoot (buffer);
			
		}
		
	}
	
	
	void ALSource::AddQueuedBuffer (value inBuffer) {
		
		if (bufferRef) {
			
			delete bufferRef;
			bufferRef = NULL;
			
		}
		
		ALBuffer* buffer = val_to_ALBuffer (inBuffer);
		std::map<ALuint, AutoGCRoot*>::iterator it = queuedBuffers.find (buffer->buffer);
		
		if (it != queuedBuffers.end ()) {
			
			AutoGCRoot* root = it->second;
			root->set (inBuffer);
			
		} else {
			
			queuedBuffers[buffer->buffer] = new AutoGCRoot (inBuffer);
			
		}
		
	}
	
	
	value ALSource::RemoveQueuedBufferById (ALuint id) {
		
		std::map<ALuint, AutoGCRoot*>::iterator it = queuedBuffers.find (id);
		
		if (it != queuedBuffers.end ()) {
			
			AutoGCRoot* root = it->second;
			queuedBuffers.erase (it);
			value ret = root->get ();
			delete root;
			return ret;
			
		} else {
			
			return alloc_null ();
			
		}
		
		
	}
	
	
	void gc_ALSource (value inHandle) {
		
		ALSource* source = (ALSource*)val_data (inHandle);
		delete source;
		
	}
	
	
	ALSource* val_to_ALSource (value inHandle) {
		
		return lime_abstract_to_pointer<ALSource> (inHandle, Kinds::Get ()->ALSource);
		
	}
	
	
	value ALSource_to_val (ALSource* inInstance) {
		
		return CFFIPointer (inInstance, gc_ALSource, Kinds::Get ()->ALSource);
		
	}
	
	
}