#ifndef LIME_APP_APPLICATION_H
#define LIME_APP_APPLICATION_H


#include <hx/CFFI.h>
#include <memory>
#include <utils/EventManager.h>


namespace lime {
	
	
	class Application {
		
		
		public:
			
			Application ();
			virtual ~Application () {};
			
			static Application* Create ();
			void RegisterAppEvent (value callback, value eventObject);
			void RegisterDropEvent (value callback, value eventObject);
			void RegisterGamepadEvent (value callback, value eventObject);
			void RegisterJoystickEvent (value callback, value eventObject);
			void RegisterKeyEvent (value callback, value eventObject);
			void RegisterMouseEvent (value callback, value eventObject);
			void RegisterRenderEvent (value callback, value eventObject);
			void RegisterSensorEvent (value callback, value eventObject);
			void RegisterTextEvent (value callback, value eventObject);
			void RegisterTouchEvent (value callback, value eventObject);
			void RegisterWindowEvent (value callback, value eventObject);
			
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
	
	value Application_to_val (Application *inInstance);
	Application* val_to_Application (value inHandle);
	
}


#endif