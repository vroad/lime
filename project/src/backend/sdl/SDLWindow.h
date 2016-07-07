#ifndef LIME_SDL_WINDOW_H
#define LIME_SDL_WINDOW_H


#include <SDL.h>
#include <graphics/ImageBuffer.h>
#include <ui/Window.h>


namespace lime {
	
	
	class SDLWindow : public Window {
		
		public:
			
			SDLWindow ();
			bool Init (Application* application, int width, int height, int flags, const char* title);
			~SDLWindow ();
			
			virtual void Alert (const char* message, const char* title);
			virtual void Close ();
			virtual void Focus ();
			virtual int GetDisplay ();
			virtual bool GetEnableTextEvents ();
			virtual int GetHeight ();
			virtual uint32_t GetID ();
			virtual int GetWidth ();
			virtual int GetX ();
			virtual int GetY ();
			virtual void Move (int x, int y);
			virtual void Resize (int width, int height);
			virtual void SetBorderless (bool borderless);
			virtual void SetEnableTextEvents (bool enabled);
			virtual void SetFullscreen (bool fullscreen);
			virtual void SetIcon (ImageBuffer *imageBuffer);
			virtual void SetMaximized (bool maximized);
			virtual void SetMinimized (bool minimized);
			virtual void SetResizable (bool resizable);
			virtual void SetTitle (const char* title);
			virtual void SwapWindow ();
			
			SDL_Window* sdlWindow;
		
	};
	
	
}


#endif