#ifndef LIME_UI_WINDOW_H
#define LIME_UI_WINDOW_H


#ifdef CreateWindow
#undef CreateWindow
#endif

#include <app/Application.h>
#include <graphics/ImageBuffer.h>
#include <stdint.h>


namespace lime {
	
	class Window;
	Window* CreateWindow (Application* application, int width, int height, int flags, const char* title);
	
	class Window {
		
		
		public:
			
			static Window* Create (Application* application, int width, int height, int flags, const char* title) {
				
				return CreateWindow (application, width, height, flags, title);
				
			}
			
			virtual ~Window () {};
			
			virtual void Alert (const char* message, const char* title) = 0;
			virtual void Close () = 0;
			virtual void Focus () = 0;
			virtual int GetDisplay () = 0;
			virtual bool GetEnableTextEvents () = 0;
			virtual int GetHeight () = 0;
			virtual uint32_t GetID () = 0;
			virtual int GetWidth () = 0;
			virtual int GetX () = 0;
			virtual int GetY () = 0;
			virtual void Move (int x, int y) = 0;
			virtual void Resize (int width, int height) = 0;
			virtual void SetBorderless (bool borderless) = 0;
			virtual void SetEnableTextEvents (bool enable) = 0;
			virtual void SetFullscreen (bool fullscreen) = 0;
			virtual void SetIcon (ImageBuffer *imageBuffer) = 0;
			virtual void SetMaximized (bool minimized) = 0;
			virtual void SetMinimized (bool minimized) = 0;
			virtual void SetResizable (bool resizable) = 0;
			virtual void SetTitle (const char* title) = 0;
			virtual void SwapWindow () = 0;
			
			Application* currentApplication;
			int flags;
		
		
	};
	
	
	enum WindowFlags {
		
		WINDOW_FLAG_FULLSCREEN = 0x00000001,
		WINDOW_FLAG_BORDERLESS = 0x00000002,
		WINDOW_FLAG_RESIZABLE = 0x00000004,
		WINDOW_FLAG_HARDWARE = 0x00000008,
		WINDOW_FLAG_VSYNC = 0x00000010,
		WINDOW_FLAG_HW_AA = 0x00000020,
		WINDOW_FLAG_HW_AA_HIRES = 0x00000060,
		WINDOW_FLAG_ALLOW_SHADERS = 0x00000080,
		WINDOW_FLAG_REQUIRE_SHADERS = 0x00000100,
		WINDOW_FLAG_DEPTH_BUFFER = 0x00000200,
		WINDOW_FLAG_STENCIL_BUFFER = 0x00000400,
		WINDOW_FLAG_ALLOW_HIGHDPI = 0x00000800
		
	};
	
	value Window_to_val (Window *inInstance);
	
	Window* val_to_Window (value inHandle);
	
}


#endif
