#ifndef LIME_UTILS_EVENT_MANAGER_H
#define LIME_UTILS_EVENT_MANAGER_H

#include <hx/CFFI.h>
#include <memory>

namespace lime {
	
	
	class EventManager {
		
	public:
		
		EventManager ();
		
		void set (value callback, value eventObject);
		
		std::unique_ptr<AutoGCRoot> callback;
		std::unique_ptr<AutoGCRoot> eventObject;
		
	};
	
	
}


#endif