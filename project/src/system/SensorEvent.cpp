#include <hx/CFFI.h>
#include <system/SensorEvent.h>
#include <utils/StringId.h>


namespace lime {
	
	
	SensorEvent::SensorEvent () {
		
		type = SENSOR_ACCELEROMETER;
		id = 0;
		x = 0;
		y = 0;
		z = 0;
		
	}
	
	
	void SensorEvent::Dispatch (Application* app, SensorEvent* event) {
		
		value callback = app->sensorEventManager->callback->get ();
		if (!val_is_null (callback)) {
			
			value object = app->sensorEventManager->eventObject->get ();
			StringId *id = StringId::Get ();
			
			alloc_field (object, id->id, alloc_int (event->id));
			alloc_field (object, id->type, alloc_int (event->type));
			alloc_field (object, id->x, alloc_float (event->x));
			alloc_field (object, id->y, alloc_float (event->y));
			alloc_field (object, id->z, alloc_float (event->z));
			
			val_call0 (callback);
			
		}
		
	}
	
	
}