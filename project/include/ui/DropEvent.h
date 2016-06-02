#ifndef LIME_UI_DROP_EVENT_H
#define LIME_UI_DROP_EVENT_H


#include <hx/CFFI.h>
#include <app/Application.h>


namespace lime {
	
	
	enum DropEventType {
		
		DROP_FILE
		
	};
	
	
	class DropEvent {
		
		public:
			
			DropEvent ();
			
			static void Dispatch (Application* app, DropEvent* event);
			
			char* file;
			DropEventType type;
		
	};
	
	
}


#endif