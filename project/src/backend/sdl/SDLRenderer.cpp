#include "SDLWindow.h"
#include "SDLRenderer.h"

namespace lime {
	
	
	SDLRenderer::SDLRenderer () {
		
		currentWindow = NULL;
		sdlRenderer = NULL;
		sdlWindow = NULL;
		sdlTexture = NULL;
		
		width = 0;
		height = 0;
		
	}
		
	bool SDLRenderer::Init (Window* window) {
		
		currentWindow = window;
		sdlWindow = ((SDLWindow*)window)->sdlWindow;
		
		int sdlFlags = 0;
		sdlFlags |= SDL_RENDERER_SOFTWARE;
		
		sdlRenderer = SDL_CreateRenderer (sdlWindow, -1, sdlFlags);
		return sdlRenderer != NULL;
		
	}
	
	
	SDLRenderer::~SDLRenderer () {
		
		if (sdlRenderer) {
			
			SDL_DestroyRenderer (sdlRenderer);
			
		}
		
	}
	
	
	void SDLRenderer::Flip () {
		
		SDL_RenderPresent (sdlRenderer);
		
	}
	
	
	double SDLRenderer::GetScale () {
		
		int outputWidth;
		int outputHeight;
		
		SDL_GetRendererOutputSize (sdlRenderer, &outputWidth, &outputHeight);
		
		int width;
		int height;
		
		SDL_GetWindowSize (sdlWindow, &width, &height);
		
		double scale = outputWidth / width;
		return scale;
		
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
			#ifndef LIME_NO_RAW_POINTER_ACCESS
			alloc_field (result, val_id ("pixels"), alloc_float ((intptr_t)pixels));
			#else
			alloc_field (result, val_id ("pixels"), alloc_null ());
			#endif
			alloc_field (result, val_id ("pitch"), alloc_int (pitch));
			
		}
		
		return result;
		
	}
	
	
	void SDLRenderer::ReadPixels (ImageBuffer *buffer, Rectangle *rect) {
		
		if (sdlRenderer) {
			
			SDL_Rect bounds = { 0, 0, 0, 0 };
			
			if (rect) {
				
				bounds.x = rect->x;
				bounds.y = rect->y;
				bounds.w = rect->width;
				bounds.h = rect->height;
				
			} else {
				
				SDL_GetWindowSize (sdlWindow, &bounds.w, &bounds.h);
				
			}
			
			buffer->Resize (bounds.w, bounds.h, 32);
			
			SDL_RenderReadPixels (sdlRenderer, &bounds, SDL_PIXELFORMAT_ABGR8888, buffer->data->Data (), buffer->Stride ());
			
			for (unsigned char *it=buffer->data->Data()+3; it<(buffer->data->Data()+buffer->data->Length());it+=4) {
				*it = 0xff;
			}

		}
		
	}
	
	
	void SDLRenderer::Unlock () {
		
		if (sdlTexture) {
			
			SDL_UnlockTexture (sdlTexture);
			SDL_RenderClear (sdlRenderer);
			SDL_RenderCopy (sdlRenderer, sdlTexture, NULL, NULL);
			
		}
		
	}
	
	
	Renderer* CreateRenderer (Window* window) {
		
		SDLRenderer *renderer = new SDLRenderer ();
		
		if (!renderer->Init (window)) {
			
			delete renderer;
			return NULL;
			
		}
		
		return renderer;
		
	}
	
	
}