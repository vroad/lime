#include <hx/CFFI.h>
#include <ui/TextEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	TextEvent::TextEvent () {
		
		length = 0;
		start = 0;
		windowID = 0;
		
	}
	
	
	void TextEvent::Dispatch (Application* app, TextEvent* event) {
		
		value callback = app->textEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->textEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			if (event->type != TEXT_INPUT) {
				
				alloc_field (object, id->length, alloc_int (event->length));
				alloc_field (object, id->start, alloc_int (event->start));
				
			}
			
			alloc_field (object, id->text, alloc_string (event->text));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->windowID, alloc_int (event->windowID));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}