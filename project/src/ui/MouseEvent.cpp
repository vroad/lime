#include <hx/CFFI.h>
#include <ui/MouseEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	MouseEvent::MouseEvent () {
		
		button = 0;
		type = MOUSE_DOWN;
		windowID = 0;
		x = 0.0;
		y = 0.0;
		movementX = 0.0;
		movementY = 0.0;
		
	}
	
	
	void MouseEvent::Dispatch (Application* app, MouseEvent* event) {
		
		value callback = app->mouseEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			StringId* id = StringId::Get ();
			
			value object = app->mouseEventManager->eventObject->get ();
			
			if (event->type != MOUSE_WHEEL) {
				
				alloc_field (object, id->button, alloc_int (event->button));
				
			}
			
			alloc_field (object, id->movementX, alloc_float (event->movementX));
			alloc_field (object, id->movementY, alloc_float (event->movementY));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->windowID, alloc_int (event->windowID));
			alloc_field (object, id->x, alloc_float (event->x));
			alloc_field (object, id->y, alloc_float (event->y));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}