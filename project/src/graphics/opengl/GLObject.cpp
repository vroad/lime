#include <graphics/opengl/GLObject.h>
#include <graphics/opengl/GLContext.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

#include <assert.h>

namespace lime {
	
	GLObject::GLObject (GLContext* context, GLuint id) {
		
		this->context = context;
		this->id = id;
		assert (id != 0);
		context->AddWeakRef ();
		
	}
	
	GLObject::~GLObject () {
		
		context->ReleaseWeakRef ();
		
	}
	
	bool GLObject::AddToDeletionQueue (GLResourceType type) {
		
		assert (id != 0);
		if (!context->IsDisposed ()) {
			
			context->AddGLObjectToDeletionQueue (this, type);
			return true;
			
		}
		
		return false;
		
	}
	
	template <GLResourceType T>
	void gc_GLObject (value handle) {
		
		GLObject* data = (GLObject*)val_data (handle);
		
		if (!data->AddToDeletionQueue (T)) {
			
			delete data;
			
		}
		
		free_abstract (handle);
		
	}
	
	value GLBuffer_to_val (GLBuffer *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_BUFFER>, Kinds::Get ()->GLBuffer);
		
	}
	
	GLBuffer* val_to_GLBuffer (value inHandle) {
		
		return lime_abstract_to_pointer<GLBuffer> (inHandle, Kinds::Get ()->GLBuffer);
		
	}
	
	value GLFramebuffer_to_val (GLFramebuffer *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_FRAMEBUFFER>, Kinds::Get ()->GLFramebuffer);
		
	}
	
	GLFramebuffer* val_to_GLFramebuffer (value inHandle) {
		
		return lime_abstract_to_pointer<GLFramebuffer> (inHandle, Kinds::Get ()->GLFramebuffer);
		
	}
	
	GLProgram* val_to_GLProgram (value inHandle) {
		
		return lime_abstract_to_pointer<GLProgram> (inHandle, Kinds::Get ()->GLProgram);
		
	}
	
	value GLProgram_to_val (GLProgram *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_PROGRAM>, Kinds::Get ()->GLProgram);	
		
	}
	
	value GLRenderbuffer_to_val (GLRenderbuffer *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_RENDERBUFFER>, Kinds::Get ()->GLRenderbuffer);
		
	}
	
	GLRenderbuffer* val_to_GLRenderbuffer (value inHandle) {
		
		return lime_abstract_to_pointer<GLRenderbuffer> (inHandle, Kinds::Get ()->GLRenderbuffer);
		
	}
	
	value GLShader_to_val (GLShader *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_SHADER>, Kinds::Get ()->GLShader);
		
	}
	
	GLShader* val_to_GLShader (value inHandle) {
		
		return lime_abstract_to_pointer<GLShader> (inHandle, Kinds::Get ()->GLShader);
		
	}
	
	value GLTexture_to_val (GLTexture *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLObject<GL_RESOURCE_TEXTURE>, Kinds::Get ()->GLTexture);
		
	}
	
	GLTexture* val_to_GLTexture (value inHandle) {
		
		return lime_abstract_to_pointer<GLTexture> (inHandle, Kinds::Get ()->GLTexture);
		
	}
	
}