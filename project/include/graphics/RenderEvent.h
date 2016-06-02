#ifndef LIME_GRAPHICS_RENDER_EVENT_H
#define LIME_GRAPHICS_RENDER_EVENT_H


#include <hx/CFFI.h>
#include <app/Application.h>


namespace lime {
	
	
	enum RenderEventType {
		
		RENDER,
		RENDER_CONTEXT_LOST,
		RENDER_CONTEXT_RESTORED
		
	};
	
	
	class RenderEvent {
		
		public:
			
			RenderEvent ();
			
			static void Dispatch (Application* app, RenderEvent* event);
			
			RenderEventType type;
		
	};
	
	
}


#endif