#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "../../graphics/opengl/OpenGLBindings.h"
#ifdef HX_WINDOWS
#include <Dwmapi.h>
#endif

namespace lime {
	
	
	SDLRenderer::SDLRenderer (Window* window) {
		
		currentWindow = window;
		originalFlags = window->flags;
		sdlWindow = ((SDLWindow*)window)->sdlWindow;
		sdlTexture = 0;
		context = 0;
		
		width = 0;
		height = 0;
		
		int sdlFlags = 0;
		
		if (window->flags & WINDOW_FLAG_HARDWARE) {
			
			sdlFlags |= SDL_RENDERER_ACCELERATED;
			
			if (window->flags & WINDOW_FLAG_VSYNC) {
				
				sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
				
			}
			
		} else {
			
			sdlFlags |= SDL_RENDERER_SOFTWARE;
			
		}
		
		if (window->flags & WINDOW_FLAG_VSYNC) {
			
			#ifdef HX_WINDOWS
			if (!(window->flags & WINDOW_FLAG_HARDWARE))
				sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
			#else
			sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
			#endif
			
		}
		
		sdlRenderer = SDL_CreateRenderer (sdlWindow, -1, sdlFlags);
		
		if (!sdlRenderer && (sdlFlags & SDL_RENDERER_ACCELERATED)) {
			
			sdlFlags &= ~SDL_RENDERER_ACCELERATED;
			// sdlFlags &= ~SDL_RENDERER_PRESENTVSYNC;
			
			sdlFlags |= SDL_RENDERER_SOFTWARE;
			
			sdlRenderer = SDL_CreateRenderer (sdlWindow, -1, sdlFlags);
			
		}
		
		if (!sdlRenderer) {
			
			printf ("Could not create SDL renderer: %s.\n", SDL_GetError ());
			
		} else {
			
			#if HX_WINDOWS
			
			isDwmFlushEnabled = false;
			isVsyncForced = false;
			if (window->flags & WINDOW_FLAG_HARDWARE && window->flags & WINDOW_FLAG_VSYNC) {
				
				bool useDwmFlush;
				isVsyncForced = SDL_GL_GetSwapInterval() != 0;
				if (!isVsyncForced) {
					
					useDwmFlush = (window->flags & WINDOW_FLAG_FULLSCREEN) ? false : true;
					
				}
				else {
					
					useDwmFlush = false;
					
				}
				
				SetDwmFlushEnabled (useDwmFlush);
				
			}
			#endif
			
		}
		
		context = SDL_GL_GetCurrentContext ();
		
		OpenGLBindings::Init ();
		
	}
	
	
	SDLRenderer::~SDLRenderer () {
		
		if (sdlRenderer) {
			
			SDL_DestroyRenderer (sdlRenderer);
			
		}
		
	}
	
	
	void SDLRenderer::Flip () {
		
		SDL_RenderPresent (sdlRenderer);
		#ifdef HX_WINDOWS
		BOOL isCompositionEnabled;
		if (currentWindow->flags & WINDOW_FLAG_HARDWARE && currentWindow->flags & WINDOW_FLAG_VSYNC) {
			
			if (isDwmFlushEnabled) {
				
				DwmIsCompositionEnabled (&isCompositionEnabled);
				if (isCompositionEnabled)
				{
					
					DwmFlush ();
					
				} else {
					
					SetDwmFlushEnabled (false);
					
				
				}
			
			} else if (!isVsyncForced && !(currentWindow->flags & WINDOW_FLAG_FULLSCREEN)) {
				
				SetDwmFlushEnabled(true);
				
				
			}
			
		} else if (currentWindow->flags & WINDOW_FLAG_HARDWARE && !(currentWindow->flags & WINDOW_FLAG_VSYNC) && originalFlags & WINDOW_FLAG_VSYNC && !(currentWindow->flags & WINDOW_FLAG_FULLSCREEN))
		{
			
			SetDwmFlushEnabled (true);
			
		}
		#endif
		
	}
	
	
	void* SDLRenderer::GetContext () {
		
		return context;
		
	}
	
	
	value SDLRenderer::Lock () {
		
		int width;
		int height;
		
		SDL_GetRendererOutputSize (sdlRenderer, &width, &height);
		
		if (width != this->width || height != this->height) {
			
			if (sdlTexture) {
				
				SDL_DestroyTexture (sdlTexture);
				
			}
			
			sdlTexture = SDL_CreateTexture (sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
			
		}
		
		value result = alloc_empty_object ();
		
		void *pixels;
		int pitch;
		
		if (SDL_LockTexture (sdlTexture, NULL, &pixels, &pitch) == 0) {
			
			alloc_field (result, val_id ("width"), alloc_int (width));
			alloc_field (result, val_id ("height"), alloc_int (height));
			alloc_field (result, val_id ("pixels"), alloc_float ((intptr_t)pixels));
			alloc_field (result, val_id ("pitch"), alloc_int (pitch));
			
		}
		
		return result;
		
	}
	
	
	void SDLRenderer::MakeCurrent () {
		
		if (sdlWindow && context) {
			
			SDL_GL_MakeCurrent (sdlWindow, context);
			
		}
		
	}
	
	
	const char* SDLRenderer::Type () {
		
		if (sdlRenderer) {
			
			SDL_RendererInfo info;
			SDL_GetRendererInfo (sdlRenderer, &info);
			
			if (info.flags & SDL_RENDERER_SOFTWARE) {
				
				return "software";
				
			} else {
				
				return "opengl";
				
			}
			
		}
		
		return "none";
		
	}
	
	
	void SDLRenderer::Unlock () {
		
		if (sdlTexture) {
			
			SDL_UnlockTexture (sdlTexture);
			SDL_RenderClear (sdlRenderer);
			SDL_RenderCopy (sdlRenderer, sdlTexture, NULL, NULL);
			
		}
		
	}
	
	#ifdef HX_WINDOWS
	void SDLRenderer::SetDwmFlushEnabled (bool enabled) {
		
		BOOL isCompositionEnabled;
		if (enabled) {
			
			DwmIsCompositionEnabled (&isCompositionEnabled);
			if (isCompositionEnabled) {
				
				SDL_GL_SetSwapInterval (0);
				if (SDL_GL_GetSwapInterval () == 0) {
					
					isDwmFlushEnabled = true;
					
				}
				
			} else {
				
				isDwmFlushEnabled = false;
				currentWindow->flags &= ~WINDOW_FLAG_VSYNC;
				
			}
			
		} else {
			
			SDL_GL_SetSwapInterval (1);
			isDwmFlushEnabled = false;
			if (SDL_GL_GetSwapInterval () == 0) {
				
				currentWindow->flags &= ~WINDOW_FLAG_VSYNC;
				
			} else {
				
				currentWindow->flags |= WINDOW_FLAG_VSYNC;
				
			}
			
		}
		
	}
	#endif

	Renderer* CreateRenderer (Window* window) {
		
		return new SDLRenderer (window);
		
	}
	
	
}