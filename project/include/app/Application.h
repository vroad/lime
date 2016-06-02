#ifndef LIME_APP_APPLICATION_H
#define LIME_APP_APPLICATION_H


#include <hx/CFFI.h>
#include <memory>
#include <utils/EventManager.h>


namespace lime {
	
	
	class Application {
		
		
		public:
			
			Application () {
				
				appEventManager.reset (new EventManager ());
				dropEventManager.reset (new EventManager ());
				gamepadEventManager.reset (new EventManager ());
				joystickEventManager.reset (new EventManager ());
				keyEventManager.reset (new EventManager ());
				mouseEventManager.reset (new EventManager ());
				renderEventManager.reset (new EventManager ());
				sensorEventManager.reset (new EventManager ());
				textEventManager.reset (new EventManager ());
				touchEventManager.reset (new EventManager ());
				windowEventManager.reset (new EventManager ());
				
			}
			
			virtual ~Application () {};
			
			virtual int Exec () = 0;
			virtual void Init () = 0;
			virtual int Quit () = 0;
			virtual void SetFrameRate (double frameRate) = 0;
			virtual bool Update () = 0;
			
			std::unique_ptr<EventManager> appEventManager;
			std::unique_ptr<EventManager> dropEventManager;
			std::unique_ptr<EventManager> gamepadEventManager;
			std::unique_ptr<EventManager> joystickEventManager;
			std::unique_ptr<EventManager> keyEventManager;
			std::unique_ptr<EventManager> mouseEventManager;
			std::unique_ptr<EventManager> renderEventManager;
			std::unique_ptr<EventManager> sensorEventManager;
			std::unique_ptr<EventManager> textEventManager;
			std::unique_ptr<EventManager> touchEventManager;
			std::unique_ptr<EventManager> windowEventManager;
			
	};
	
	
	Application* CreateApplication ();
	
	
}


#endif