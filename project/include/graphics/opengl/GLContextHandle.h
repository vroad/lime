#ifndef LIME_GRAPHICS_OPENGL_GL_CONTEXT_H
#define LIME_GRAPHICS_OPENGL_GL_CONTEXT_H

#include <ui/Window.h>

namespace lime {
	
	class GLContextHandle {
		
		
		public:
			
			virtual ~GLContextHandle () {};
			virtual bool MakeCurrent () = 0;
			
			static GLContextHandle* Create (value inWindow);
			
			static bool ClearCurrent ();
			
			
	};
	
}


#endif