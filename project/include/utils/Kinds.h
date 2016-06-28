#ifndef LIME_UTILS_KINDS_H
#define LIME_UTILS_KINDS_H


#include <hx/CFFI.h>
#include <boost/scoped_ptr.hpp>

namespace lime {
	
	
	class Kinds {
		
		
	public:
		
		Kinds ();
		
		static Kinds *Get ();
		
		static void Reset ();
		
		vkind Application;
		vkind OpenGLContext;
		vkind GLBuffer;
		vkind GLContextHandle;
		vkind GLFramebuffer;
		vkind GLProgram;
		vkind GLRenderbuffer;
		vkind GLShader;
		vkind GLTexture;
		vkind Window;
		
	private:
		
		static boost::scoped_ptr<Kinds> singleton;
		
	};
	
	
}


#endif