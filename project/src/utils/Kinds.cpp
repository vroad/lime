#include <utils/Kinds.h>

namespace lime {
	
	std::unique_ptr<Kinds> Kinds::singleton;
	
	Kinds::Kinds () {
		
		this->Application = alloc_kind ();
		this->ALCContextWrapper = alloc_kind ();
		this->ALCdevice = alloc_kind ();
		this->CURL = alloc_kind ();
		this->Font = alloc_kind ();
		this->GLContext = alloc_kind ();
		this->GLBuffer = alloc_kind ();
		this->GLContextHandle = alloc_kind ();
		this->GLFramebuffer = alloc_kind ();
		this->GLProgram = alloc_kind ();
		this->GLRenderbuffer = alloc_kind ();
		this->GLShader = alloc_kind ();
		this->GLTexture = alloc_kind ();
		this->Renderer = alloc_kind ();
		this->TextLayout = alloc_kind ();
		this->Window = alloc_kind ();
		
		this->cairo_t = alloc_kind ();
		this->cairo_font_face_t = alloc_kind ();
		this->cairo_font_options_t = alloc_kind ();
		this->cairo_pattern_t = alloc_kind ();
		this->cairo_surface_t = alloc_kind ();
		
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