#include "SDLWindow.h"
#include "SDLRenderer.h"
#include "../../graphics/opengl/OpenGLBindings.h"


namespace lime {
	
	SDL_RendererInfo SDLRenderer::sdlRendererInfo = SDL_RendererInfo();
	
	SDLRenderer::SDLRenderer (Window* window) {
		
		currentWindow = window;
		sdlWindow = ((SDLWindow*)window)->sdlWindow;
		
		int sdlFlags = SDL_RENDERER_ACCELERATED;
		
		if (window->flags & WINDOW_FLAG_VSYNC) sdlFlags |= SDL_RENDERER_PRESENTVSYNC;
		
		sdlRenderer = SDL_CreateRenderer (sdlWindow, -1, sdlFlags);
		if (sdlRenderer)
			SDL_GetRendererInfo(sdlRenderer, &SDLRenderer::sdlRendererInfo);

		SDL_GL_SetSwapInterval(-1);
		
		OpenGLBindings::Init ();
	}
	
	
	SDLRenderer::~SDLRenderer () {
		
		
		
	}
	
	
	void SDLRenderer::Flip () {
		
		SDL_RenderPresent (sdlRenderer);
		
	}
	
	
	Renderer* CreateRenderer (Window* window) {
		
		return new SDLRenderer (window);
		
	}
	
	
}