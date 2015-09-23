#ifndef LIME_UTILS_KINDS_H
#define LIME_UTILS_KINDS_H

#include <hx/CFFI.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {

	class Kinds
	{
	public:

		Kinds() {}

		vkind Application;
		vkind AudioBuffer;
		vkind AudioStream;
		vkind Font;
		vkind Window;
		vkind Renderer;
		vkind TextLayout;
		vkind RendererContext;
		vkind VideoLib;
		vkind Video;

		vkind CURL;
		vkind cairo_t;
		vkind cairo_surface_t;
		vkind cairo_font_face_t;
		vkind cairo_pattern_t;
		vkind cairo_font_options_t;

		vkind ALCcontext;
		vkind ALCdevice;

		vkind JNIEnv;
	};

	Kinds GetKinds ();
}

#endif