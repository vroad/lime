#include <utils/EventManager.h>

namespace lime {
	
	EventManager::EventManager () {
		
		callback.reset (new AutoGCRoot (alloc_null ()));
		eventObject.reset (new AutoGCRoot (alloc_empty_object ()));
		
	}
	
	void EventManager::set (value callback, value eventObject) {
		
		this->callback->set (callback);
		this->eventObject->set (eventObject);
		
	}
	
}