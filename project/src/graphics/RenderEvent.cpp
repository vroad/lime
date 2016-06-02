#include <hx/CFFI.h>
#include <graphics/RenderEvent.h>


namespace lime {
	
	
	//static int id_type;
	//static bool init = false;
	
	
	RenderEvent::RenderEvent () {
		
		type = RENDER;
		
	}
	
	
	void RenderEvent::Dispatch (Application* app, RenderEvent* event) {
		
		value callback = app->renderEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			//if (!init) {
				
				//id_type = val_id ("type");
				
			//}
			
			value object = app->renderEventManager->eventObject->get ();
			
			//alloc_field (object, id_type, alloc_int (event->type));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}