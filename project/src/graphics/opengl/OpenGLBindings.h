#ifndef LIME_GRAPHICS_OPENGL_OPENGL_BINDINGS_H
#define LIME_GRAPHICS_OPENGL_OPENGL_BINDINGS_H


namespace lime {
	
	
	class OpenGLBindings {
		
		public:
			
			static bool Init ();
			
			static void* handle;
			#ifdef NATIVE_TOOLKIT_SDL_ANGLE
			static void *eglHandle;
			#endif
		
		private:
			
			static bool initialized;
		
		
	};
	
	
}


#endif