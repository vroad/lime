#include "SDLGLContextHandle.h"
#include "SDLWindow.h"
#include <utils/PointerConverter.h>

namespace lime {
	
	SDLGLContextHandle::SDLGLContextHandle () {
		
		context = NULL;
		
	}
	
	SDLGLContextHandle::~SDLGLContextHandle () {
		
		SDL_GL_DeleteContext (context);
		
	}
	
	bool SDLGLContextHandle::Init (value inWindow) {
		
		SDLWindow* windowPtr = (SDLWindow*)val_to_Window (inWindow);
		windowHandle.reset (new AutoGCRoot (inWindow));
		context = SDL_GL_CreateContext (windowPtr->sdlWindow);
		return context != NULL;
		
	}
	
	bool SDLGLContextHandle::MakeCurrent () {
		
		value inWindow = windowHandle->get ();
		SDLWindow* windowPtr = (SDLWindow*)val_to_Window (inWindow);
		return SDL_GL_MakeCurrent (windowPtr->sdlWindow, context) == 0;
		
	}
	
	GLContextHandle* GLContextHandle::Create (value inWindow) {
		
		SDLGLContextHandle* context = new SDLGLContextHandle();
		if (!context->Init (inWindow)) {
			
			delete context;
			return NULL;
			
		}
		
		return context;
		
	}
	
	bool GLContextHandle::ClearCurrent () {
		
		return SDL_GL_MakeCurrent (NULL, NULL) == 0;
		
	}
	
}