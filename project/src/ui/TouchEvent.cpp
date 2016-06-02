#include <hx/CFFI.h>
#include <ui/TouchEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	TouchEvent::TouchEvent () {
		
		type = TOUCH_START;
		x = 0;
		y = 0;
		id = 0;
		dx = 0;
		dy = 0;
		pressure = 0;
		device = 0;
		
	}
	
	
	void TouchEvent::Dispatch (Application* app, TouchEvent* event) {
		
		value callback = app->touchEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			StringId* id = StringId::Get ();
			value object = app->touchEventManager->eventObject->get ();
			
			alloc_field (object, id->device, alloc_int (event->device));
			alloc_field (object, id->dx, alloc_float (event->dx));
			alloc_field (object, id->dy, alloc_float (event->dy));
			alloc_field (object, id->id, alloc_int (event->id));
			alloc_field (object, id->pressure, alloc_float (event->pressure));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->x, alloc_float (event->x));
			alloc_field (object, id->y, alloc_float (event->y));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}