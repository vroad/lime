#include "SDLOpenGLContext.h"
#include "SDLWindow.h"

namespace lime {
	
	SDLOpenGLContext::SDLOpenGLContext () {
		
		context = NULL;
		
	}
	
	SDLOpenGLContext::~SDLOpenGLContext () {
		
		SDL_GL_DeleteContext (context);
		
	}
	
	bool SDLOpenGLContext::Init (SDL_Window* window) {
		
		context = SDL_GL_CreateContext(window);
		return context != NULL;
		
	}
	
	bool SDLOpenGLContext::MakeCurrent (Window *window) {
		
		SDLWindow* windowPtr = (SDLWindow*)window;
		return SDL_GL_MakeCurrent (windowPtr->sdlWindow, context) == 0;
		
	}
	
	OpenGLContext* CreateOpenGLContext (Window* window) {
		
		if (!window) {
			
			return NULL;
			
		}
		
		SDLWindow* windowPtr = (SDLWindow*)window;
		SDLOpenGLContext* context = new SDLOpenGLContext();
		if (!context->Init(windowPtr->sdlWindow)) {
			
			delete context;
			return NULL;
			
		}
		
		return context;
		
	}
	
	bool ClearCurrentOpenGLContext () {
		
		return SDL_GL_MakeCurrent (NULL, NULL) == 0;
		
	}
	
	void SwapWindow (Window* window) {
		
		SDL_GL_SwapWindow (((SDLWindow*)window)->sdlWindow);
		
	}
	
}