#ifndef LIME_GRAPHICS_OPENGL_GL_OBJECT_H
#define LIME_GRAPHICS_OPENGL_GL_OBJECT_H

#include <hx/CFFI.h>
#include <graphics/opengl/GLResourceType.h>
#include "OpenGL.h"

namespace lime {
	
	class GLContext;
	
	class GLObject {
		
	public:
		
		GLObject (GLContext* context, GLuint id);
		~GLObject ();
		bool AddToDeletionQueue (GLResourceType type);
		
		GLuint id;
		
	private:
		
		GLContext* context;
		
	};
	
	typedef GLObject GLBuffer;
	typedef GLObject GLFramebuffer;
	typedef GLObject GLProgram;
	typedef GLObject GLRenderbuffer;
	typedef GLObject GLShader;
	typedef GLObject GLTexture;
	
	value GLBuffer_to_val(GLBuffer *inInstance);
	
	GLBuffer* val_to_GLBuffer(value inHandle);
	
	value GLFramebuffer_to_val(GLFramebuffer *inInstance);
	
	GLFramebuffer* val_to_GLFramebuffer(value inHandle);
	
	value GLProgram_to_val(GLProgram *inInstance);
	
	GLProgram* val_to_GLProgram(value inHandle);
	
	value GLRenderbuffer_to_val(GLRenderbuffer *inInstance);
	
	GLRenderbuffer* val_to_GLRenderbuffer(value inHandle);
	
	value GLShader_to_val(GLShader *inInstance);
	
	GLShader* val_to_GLShader(value inHandle);
	
	value GLTexture_to_val(GLTexture *inInstance);
	
	GLTexture* val_to_GLTexture(value inHandle);
	
}

#endif