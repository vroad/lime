#ifndef LIME_SDL_OPENGL_CONTEXT_H
#define LIME_SDL_OPENGL_CONTEXT_H


#include <SDL.h>
#include <graphics/opengl/GLContextHandle.h>
#include <hx/CFFI.h>
#include <memory>

namespace lime {
	
	
	class SDLGLContextHandle : public GLContextHandle {
		
		public:
			
			SDLGLContextHandle ();
			~SDLGLContextHandle ();
			bool Init (value inWindow);
			bool MakeCurrent ();
			
		private:
			
			SDL_GLContext context;
			std::unique_ptr<AutoGCRoot> windowHandle;
			
	};
	
	
}


#endif