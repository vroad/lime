#include <hx/CFFI.h>
#include <ui/GamepadEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	AutoGCRoot* GamepadEvent::callback = 0;
	AutoGCRoot* GamepadEvent::eventObject = 0;
	
	
	GamepadEvent::GamepadEvent () {
		
		axis = 0;
		axisValue = 0;
		button = 0;
		id = 0;
		type = GAMEPAD_AXIS_MOVE;
		
	}
	
	
	void GamepadEvent::Dispatch (Application* app, GamepadEvent* event) {
		
		value callback = app->gamepadEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->gamepadEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			alloc_field (object, id->axis, alloc_int (event->axis));
			alloc_field (object, id->button, alloc_int (event->button));
			alloc_field (object, id->id, alloc_int (event->id));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->value, alloc_float (event->axisValue));
			
			val_call0 (GamepadEvent::callback->get ());
			
		}
		
	}
	
	
}