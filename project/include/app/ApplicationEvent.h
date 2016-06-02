#ifndef LIME_APP_APPLICATION_EVENT_H
#define LIME_APP_APPLICATION_EVENT_H


#include <hx/CFFI.h>
#include <app/Application.h>


namespace lime {
	
	
	enum ApplicationEventType {
		
		UPDATE,
		EXIT
		
	};
	
	
	class ApplicationEvent {
		
		public:
			
			ApplicationEvent ();
			
			static void Dispatch (Application* app, ApplicationEvent* event);
			
			int deltaTime;
			ApplicationEventType type;
		
	};
	
	
}


#endif