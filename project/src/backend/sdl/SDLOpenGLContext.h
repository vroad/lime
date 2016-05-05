#ifndef LIME_SDL_OPENGL_CONTEXT_H
#define LIME_SDL_OPENGL_CONTEXT_H


#include <SDL.h>
#include <graphics/OpenGLContext.h>

namespace lime {
	
	
	class SDLOpenGLContext : public OpenGLContext {
		
		public:
			
			SDLOpenGLContext ();
			~SDLOpenGLContext ();
			bool Init (SDL_Window* window);
			bool MakeCurrent (Window *window);
			
		private:
			
			SDL_GLContext context;
			
	};
	
	
}


#endif