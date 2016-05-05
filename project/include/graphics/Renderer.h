#ifndef LIME_GRAPHICS_RENDERER_H
#define LIME_GRAPHICS_RENDERER_H


#include <graphics/ImageBuffer.h>
#include <math/Rectangle.h>
#include <ui/Window.h>
#include <hx/CFFI.h>


namespace lime {
	
	
	class Renderer {
		
		
		public:

			virtual ~Renderer() {};
			
			virtual void Flip () = 0;
			virtual double GetScale () = 0;
			virtual value Lock () = 0;
			virtual void ReadPixels (ImageBuffer *buffer, Rectangle *rect) = 0;
			virtual void Unlock () = 0;
			
			Window* currentWindow;
		
		
	};
	
	
	Renderer* CreateRenderer (Window* window);
	
	
}


#endif