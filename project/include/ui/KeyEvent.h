#ifndef LIME_UI_KEY_EVENT_H
#define LIME_UI_KEY_EVENT_H


#include <hx/CFFI.h>
#include <stdint.h>
#include <app/Application.h>


namespace lime {
	
	
	enum KeyEventType {
		
		KEY_DOWN,
		KEY_UP
		
	};
	
	
	class KeyEvent {
		
		public:
			
			KeyEvent ();
			
			static void Dispatch (Application* app, KeyEvent* event);
			
			double keyCode;
			int modifier;
			KeyEventType type;
			uint32_t windowID;
		
	};
	
	
}


#endif