#include <hx/CFFI.h>
#include <ui/JoystickEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	AutoGCRoot* JoystickEvent::callback = 0;
	AutoGCRoot* JoystickEvent::eventObject = 0;
	
	
	JoystickEvent::JoystickEvent () {
		
		id = 0;
		index = 0;
		eventValue = 0;
		x = 0;
		y = 0;
		type = JOYSTICK_AXIS_MOVE;
		
	}
	
	
	void JoystickEvent::Dispatch (Application* app, JoystickEvent* event) {
		
		value callback = app->joystickEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->joystickEventManager->eventObject->get ();
			StringId*id = StringId::Get ();
			
			alloc_field (object, id->id, alloc_int (event->id));
			alloc_field (object, id->index, alloc_int (event->index));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->value, alloc_float (event->eventValue));
			alloc_field (object, id->x, alloc_int (event->x));
			alloc_field (object, id->y, alloc_int (event->y));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}