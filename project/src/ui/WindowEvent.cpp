#include <hx/CFFI.h>
#include <ui/WindowEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	WindowEvent::WindowEvent () {
		
		type = WINDOW_ACTIVATE;
		
		width = 0;
		height = 0;
		windowID = 0;
		x = 0;
		y = 0;
		
	}
	
	
	void WindowEvent::Dispatch (Application* app, WindowEvent* event) {
		
		value callback = app->windowEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->windowEventManager->eventObject->get ();
			StringId* id = StringId::Get ();
			
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->windowID, alloc_int (event->windowID));
			
			switch (event->type) {
				
				case WINDOW_MOVE:
					
					alloc_field (object, id->x, alloc_int (event->x));
					alloc_field (object, id->y, alloc_int (event->y));
					break;
				
				case WINDOW_RESIZE:
					
					alloc_field (object, id->width, alloc_int (event->width));
					alloc_field (object, id->height, alloc_int (event->height));
					break;
				
				default: break;
				
			}
			
			val_call0 (callback);
			
		}
		
	}
	
	
}