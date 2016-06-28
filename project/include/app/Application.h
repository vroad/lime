#ifndef LIME_APP_APPLICATION_H
#define LIME_APP_APPLICATION_H


#include <hx/CFFI.h>


namespace lime {
	
	
	class Application {
		
		
		public:
			
			
			static Application* Create ();
			
			virtual ~Application () {};
			
			static AutoGCRoot* callback;
			
			virtual int Exec () = 0;
			virtual void Init () = 0;
			virtual int Quit () = 0;
			virtual void SetFrameRate (double frameRate) = 0;
			virtual bool Update () = 0;
		
		
	};
	
	value Application_to_val (Application *inInstance);
	Application* val_to_Application (value inHandle);
	
	
}


#endif