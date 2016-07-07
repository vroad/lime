#include <app/Application.h>
#include <utils/Kinds.h>
#include <utils/PointerUtils.h>

namespace lime {
	
	
	Application::Application () {
		
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
	
	
	void Application::RegisterAppEvent (value callback, value eventObject) {
		
		appEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterDropEvent (value callback, value eventObject) {
		
		dropEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterGamepadEvent (value callback, value eventObject) {
		
		gamepadEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterJoystickEvent (value callback, value eventObject) {
		
		joystickEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterKeyEvent (value callback, value eventObject) {
		
		keyEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterMouseEvent (value callback, value eventObject) {
		
		mouseEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterRenderEvent (value callback, value eventObject) {
		
		renderEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterSensorEvent (value callback, value eventObject) {
		
		sensorEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterTextEvent (value callback, value eventObject) {
		
		textEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterTouchEvent (value callback, value eventObject) {
		
		touchEventManager->set (callback, eventObject);
		
	}
	
	void Application::RegisterWindowEvent (value callback, value eventObject) {
		
		windowEventManager->set (callback, eventObject);
		
	}
	
	
	value Application_to_val (Application *inInstance) {
		
		return CFFIPointer (inInstance, lime_destroy_abstract<Application>, Kinds::Get ()->Application);
		
	}
	
	
	lime::Application* val_to_Application(value inHandle) {
		
		return lime_abstract_to_pointer<Application> (inHandle, Kinds::Get ()->Application);
		
	}
	
	
}