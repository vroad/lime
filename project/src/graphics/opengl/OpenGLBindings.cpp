//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <utils/Bytes.h>
#include <graphics/opengl/OpenGL.h>
#include <graphics/opengl/OpenGLBindings.h>
#include <string>

#ifdef NEED_EXTENSIONS
#define DECLARE_EXTENSION
#include <graphics/opengl/OpenGLExtensions.h>
#undef DECLARE_EXTENSION
#endif

#ifdef HX_LINUX
#include <dlfcn.h>
#endif

#ifdef LIME_SDL
#include <SDL.h>
#endif

#include <utils/Exception.h>

namespace lime {
	
	
	bool OpenGLBindings::initialized = false;
	std::unique_ptr<void, UnixLibraryDeleter> OpenGLBindings::handle;
	#ifdef NATIVE_TOOLKIT_SDL_ANGLE
	std::unique_ptr<void, WinLibraryDeleter> OpenGLBindings::eglHandle;
	#endif
	
	
	bool OpenGLBindings::Init () {
		
		static bool result = true;
		
		if (!initialized) {
			
			initialized = true;
			
			#ifdef HX_LINUX
			
			OpenGLBindings::handle.reset (dlopen ("libGL.so.1", RTLD_NOW|RTLD_GLOBAL));
			
			if (!OpenGLBindings::handle) {
				
				OpenGLBindings::handle.reset (dlopen ("libGL.so", RTLD_NOW|RTLD_GLOBAL));
				
			}
			
			if (!OpenGLBindings::handle) {
				
				result = false;
				return result;
				
			}
			
			#elif defined (NATIVE_TOOLKIT_SDL_ANGLE)
			
			OpenGLBindings::eglHandle.reset (LoadLibrary (L"libegl.dll"));
			
			if (!OpenGLBindings::eglHandle) {
				
				result = false;
				return result;
				
			}
			
			#endif
			
			#ifdef NEED_EXTENSIONS
			#define GET_EXTENSION
			#include <graphics/opengl/OpenGLExtensions.h>
			#undef DEFINE_EXTENSION
			#endif
			
		}
		
		return result;
		
	}
	
	void UnixLibraryDeleter::operator () (void *handle) const
	{
		#ifdef HX_LINUX
		dlclose (handle);
		#endif
	}
	
	void WinLibraryDeleter::operator () (void *handle) const
	{
		#ifdef NATIVE_TOOLKIT_SDL_ANGLE
		FreeLibrary ((HMODULE)handle);
		#endif
	}
	
	
}


extern "C" int lime_opengl_register_prims () {
	
	return 0;
	
}