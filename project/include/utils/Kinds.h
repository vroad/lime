#ifndef LIME_UTILS_KINDS_H
#define LIME_UTILS_KINDS_H


#include <hx/CFFI.h>
#include <memory>


namespace lime {
	
	
	class Kinds {
		
		
	public:
		
		Kinds ();
		
		static Kinds *Get ();
		
		static void Reset ();
		
		vkind Application;
		vkind ALCContextWrapper;
		vkind ALCdevice;
		vkind CURL;
		vkind Font;
		vkind GLContext;
		vkind GLBuffer;
		vkind GLContextHandle;
		vkind GLFramebuffer;
		vkind GLProgram;
		vkind GLRenderbuffer;
		vkind GLShader;
		vkind GLTexture;
		vkind Renderer;
		vkind TextLayout;
		vkind Window;
		vkind cairo_t;
		vkind cairo_font_face_t;
		vkind cairo_font_options_t;
		vkind cairo_pattern_t;
		vkind cairo_surface_t;
		
	private:
		
		static std::unique_ptr<Kinds> singleton;
		
	};
	
	
}


#endif