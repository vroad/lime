#ifndef LIME_GRAPHICS_OPENGL_CONTEXT_H
#define LIME_GRAPHICS_OPENGL_CONTEXT_H

#include <ui/Window.h>

namespace lime {
	
	
	class OpenGLContext {
		
		
		public:
			
			virtual ~OpenGLContext() {};
			virtual bool MakeCurrent(Window* window) = 0;
			
			
	};
	
	OpenGLContext* CreateOpenGLContext (Window* window);
	bool ClearCurrentOpenGLContext ();
	
	void SwapWindow (Window* window);
	
}


#endif