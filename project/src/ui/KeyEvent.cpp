#include <hx/CFFI.h>
#include <ui/KeyEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	KeyEvent::KeyEvent () {
		
		keyCode = 0;
		modifier = 0;
		type = KEY_DOWN;
		windowID = 0;
		
	}
	
	
	void KeyEvent::Dispatch (Application* app, KeyEvent* event) {
		
		value callback = app->keyEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->keyEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			alloc_field (object, id->keyCode, alloc_float (event->keyCode));
			alloc_field (object, id->modifier, alloc_int (event->modifier));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->windowID, alloc_int (event->windowID));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}