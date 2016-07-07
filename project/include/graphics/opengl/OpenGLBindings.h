#ifndef LIME_GRAPHICS_OPENGL_OPENGL_BINDINGS_H
#define LIME_GRAPHICS_OPENGL_OPENGL_BINDINGS_H

#include <memory>

namespace lime {
	
	struct UnixLibraryDeleter
	{
		void operator () (void* handle) const;
	};
	
	struct WinLibraryDeleter
	{
		void operator () (void* handle) const;
	};
	
	class OpenGLBindings {
		
		public:
			
			static bool Init ();
			
			static std::unique_ptr<void, UnixLibraryDeleter> handle;
			#ifdef NATIVE_TOOLKIT_SDL_ANGLE
			static std::unique_ptr<void, WinLibraryDeleter> eglHandle;
			#endif
		
		private:
			
			static bool initialized;
		
		
	};
	
	
}


#endif