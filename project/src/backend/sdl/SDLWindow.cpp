#include "SDLWindow.h"


namespace lime {
	
	
	SDLWindow::SDLWindow (Application* application, int width, int height, int flags, const char* title) {
		
		currentApplication = application;
		this->flags = flags;
		
		int sdlFlags = SDL_WINDOW_OPENGL;
		
		if (flags & WINDOW_FLAG_FULLSCREEN) sdlFlags |= SDL_WINDOW_FULLSCREEN;
		if (flags & WINDOW_FLAG_RESIZABLE) sdlFlags |= SDL_WINDOW_RESIZABLE;
		if (flags & WINDOW_FLAG_BORDERLESS) sdlFlags |= SDL_WINDOW_BORDERLESS;
		
		if (flags & WINDOW_FLAG_DEPTH_BUFFER) {
			
			SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 32 - (flags & WINDOW_FLAG_STENCIL_BUFFER) ? 8 : 0);
			
		}
		
		if (flags & WINDOW_FLAG_STENCIL_BUFFER) {
			
			SDL_GL_SetAttribute (SDL_GL_STENCIL_SIZE, 8);
			
		}
		
		sdlWindow = SDL_CreateWindow (title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, sdlFlags);
		
	}
	
	
	SDLWindow::~SDLWindow () {
		
		
		
	}
	
	
	void SDLWindow::Move (int x, int y) {
		
		SDL_SetWindowPosition (sdlWindow, x, y);
		
	}
	
	
	void SDLWindow::Resize (int width, int height) {
		
		SDL_SetWindowSize (sdlWindow, width, height);
		
	}
	
	
	void SDLWindow::SetIcon (ImageBuffer *imageBuffer) {
		
		SDL_Surface *surface = SDL_CreateRGBSurfaceFrom (imageBuffer->data->Bytes (), imageBuffer->width, imageBuffer->height, imageBuffer->bpp * 8, imageBuffer->width * imageBuffer->bpp, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
		
		if (surface) {
			
			SDL_SetWindowIcon (sdlWindow, surface);
			SDL_FreeSurface (surface);
			
		}
		
	}
	
	
	Window* CreateWindow (Application* application, int width, int height, int flags, const char* title) {
		
		return new SDLWindow (application, width, height, flags, title);
		
	}
	
	
}