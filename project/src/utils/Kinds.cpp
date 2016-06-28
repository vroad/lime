#include <utils/Kinds.h>

namespace lime {
	
	boost::scoped_ptr<Kinds> Kinds::singleton;
	
	Kinds::Kinds () {
		
		this->Application = alloc_kind ();
		this->OpenGLContext = alloc_kind ();
		this->GLBuffer = alloc_kind ();
		this->GLContextHandle = alloc_kind ();
		this->GLFramebuffer = alloc_kind ();
		this->GLProgram = alloc_kind ();
		this->GLRenderbuffer = alloc_kind ();
		this->GLShader = alloc_kind ();
		this->GLTexture = alloc_kind ();
		this->Window = alloc_kind ();
		
	}
	
	Kinds* Kinds::Get () {
		
		if (!singleton) {
			
			singleton.reset (new Kinds ());
			
		}
		
		return singleton.get ();
		
	}
	
	void Kinds::Reset () {
		
		if (singleton) {
			
			singleton.reset (NULL);
			
		}
		
	}
	
	
}