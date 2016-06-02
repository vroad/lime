#ifndef LIME_UI_TOUCH_EVENT_H
#define LIME_UI_TOUCH_EVENT_H


#include <hx/CFFI.h>
#include <stdint.h>
#include <app/Application.h>


namespace lime {
	
	
	enum TouchEventType {
		
		TOUCH_START,
		TOUCH_END,
		TOUCH_MOVE
		
	};
	
	
	class TouchEvent {
		
		public:
			
			TouchEvent ();
			
			static void Dispatch (Application* app, TouchEvent* event);
			
			uint32_t device;
			float dx;
			float dy;
			uint32_t id;
			float pressure;
			TouchEventType type;
			float x;
			float y;
		
	};
	
	
}


#endif