#ifndef LIME_SYSTEM_SENSOR_EVENT_H
#define LIME_SYSTEM_SENSOR_EVENT_H


#include <hx/CFFI.h>
#include <app/Application.h>


namespace lime {
	
	
	enum SensorEventType {
		
		SENSOR_ACCELEROMETER
		
	};
	
	
	class SensorEvent {
		
		public:
			
			SensorEvent ();
			
			static void Dispatch (Application* app, SensorEvent* event);
			
			int id;
			SensorEventType type;
			double x;
			double y;
			double z;
			
		
	};
	
	
}


#endif