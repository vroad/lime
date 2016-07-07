#ifndef LIME_UI_GAMEPAD_H
#define LIME_UI_GAMEPAD_H


#include <hx/CFFI.h>


namespace lime {
	
	
	class Gamepad {
		
		public:
			
			static void AddMappings (value mappings);
			static const char* GetDeviceGUID (int id);
			static const char* GetDeviceName (int id);
		
	};
	
	
}


#endif