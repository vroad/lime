#include <hx/CFFI.h>
#include <ui/DropEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	DropEvent::DropEvent () {
		
		file = 0;
		type = DROP_FILE;
		
	}
	
	
	void DropEvent::Dispatch (Application* app, DropEvent* event) {
		
		value callback = app->dropEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->dropEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			alloc_field (object, id->file, alloc_string (event->file));
			alloc_field (object, id->type, alloc_int (event->type));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}