#include <utils/Kinds.h>
#include <atomic>
#include <mutex>

namespace lime {

	std::atomic_bool gKindsInit;
	std::mutex mtx;
	Kinds gKinds;

	void InitializeKinds () {

		gKinds.Application = alloc_kind ();
		gKinds.AudioBuffer = alloc_kind ();
		gKinds.AudioStream = alloc_kind ();
		gKinds.Font = alloc_kind ();
		gKinds.Window = alloc_kind ();
		gKinds.Renderer = alloc_kind ();
		gKinds.TextLayout = alloc_kind ();
		gKinds.RendererContext = alloc_kind ();
		gKinds.VideoLib = alloc_kind ();
		gKinds.Video = alloc_kind ();
		gKinds.CURL = alloc_kind ();
		gKinds.cairo_t = alloc_kind ();
		gKinds.cairo_surface_t = alloc_kind ();
		gKinds.cairo_font_face_t = alloc_kind ();
		gKinds.cairo_pattern_t = alloc_kind ();
		gKinds.cairo_font_options_t = alloc_kind ();
		gKinds.ALCcontext = alloc_kind ();
		gKinds.ALCdevice = alloc_kind ();
		gKinds.JNIEnv = alloc_kind ();

	}

	Kinds GetKinds () {

		bool init = gKindsInit.load (std::memory_order_acquire);
		if (!init) {

			std::lock_guard<std::mutex> lock(mtx);
			InitializeKinds ();
			gKindsInit.store (true, std::memory_order_release);

		}

		return gKinds;

	}

}