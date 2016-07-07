#ifndef LIME_GRAPHICS_OPENGL_GL_RESOURCE_H
#define LIME_GRAPHICS_OPENGL_GL_RESOURCE_H


#include "GLResourceType.h"
#include "OpenGL.h"


namespace lime {
	
	class GLObject;
	
	struct GLResource {
		
		
		GLResource (GLObject* obj, GLResourceType type)	{
			
			this->obj = obj;
			this->type = type;
			
		}
		
		
		GLObject* obj;
		GLResourceType type;
		
		
	};
	
}


#endif