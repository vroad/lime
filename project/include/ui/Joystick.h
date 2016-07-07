#ifndef LIME_UI_JOYSTICK_H
#define LIME_UI_JOYSTICK_H


#include <hx/CFFI.h>


namespace lime {
	
	
	class Joystick {
		
		public:
			
			static value GetDeviceGUID (int id);
			static const char* GetDeviceName (int id);
			static int GetNumAxes (int id);
			static int GetNumButtons (int id);
			static int GetNumHats (int id);
			static int GetNumTrackballs (int id);
		
	};
	
	
}


#endif