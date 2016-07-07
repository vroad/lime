#include "SDLGamepad.h"


namespace lime {
	
	
	std::map<int, SDL_GameController*> gameControllers = std::map<int, SDL_GameController*> ();
	std::map<int, int> gameControllerIDs = std::map<int, int> ();
	
	
	bool SDLGamepad::Connect (int deviceID) {
		
		if (SDL_IsGameController (deviceID)) {
			
			SDL_GameController *gameController = SDL_GameControllerOpen (deviceID);
			
			if (gameController) {
				
				SDL_Joystick *joystick = SDL_GameControllerGetJoystick (gameController);
				int id = SDL_JoystickInstanceID (joystick);
				
				gameControllers[id] = gameController;
				gameControllerIDs[deviceID] = id;
				
				return true;
				
			}
			
		}
		
		return false;
		
	}
	
	
	bool SDLGamepad::Disconnect (int id) {
		
		if (gameControllers.find (id) != gameControllers.end ()) {
			
			SDL_GameController *gameController = gameControllers[id];
			SDL_GameControllerClose (gameController);
			gameControllers.erase (id);
			
			return true;
			
		}
		
		return false;
		
	}
	
	
	int SDLGamepad::GetInstanceID (int deviceID) {
		
		return gameControllerIDs[deviceID];
		
	}
	
	
	void Gamepad::AddMappings (value mappings) {
		
		int length = val_array_size (mappings);
		
		for (int i = 0; i < length; i++) {
			
			const char* content = val_string (val_array_i (mappings, i));
			SDL_GameControllerAddMapping (content);
			
		}
		
	}
	
	
	const char* Gamepad::GetDeviceGUID (int id) {
		
		char* guid = new char[64];
		SDL_JoystickGetGUIDString (SDL_JoystickGetDeviceGUID (id), guid, 64);
		return guid;
		
	}
	
	
	const char* Gamepad::GetDeviceName (int id) {
		
		return SDL_GameControllerName (gameControllers[id]);
		
	}
	
	
}