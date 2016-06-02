#include <hx/CFFI.h>
#include <app/ApplicationEvent.h>
#include <utils/StringId.h>

namespace lime {
	
	
	ApplicationEvent::ApplicationEvent () {
		
		deltaTime = 0;
		type = UPDATE;
		
	}
	
	
	void ApplicationEvent::Dispatch (Application* app, ApplicationEvent* event) {
		
		value callback = app->appEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->appEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			alloc_field (object, id->deltaTime, alloc_int (event->deltaTime));
			alloc_field (object, id->type, alloc_int (event->type));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}