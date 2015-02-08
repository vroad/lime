#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include <app/Application.h>
#include <app/UpdateEvent.h>
#include <audio/format/OGG.h>
#include <audio/format/WAV.h>
#include <audio/AudioBuffer.h>
#include <graphics/format/JPEG.h>
#include <graphics/format/PNG.h>
#include <graphics/Font.h>
#ifdef LIME_HARFBUZZ
#include <graphics/Text.h>
#endif
#include <graphics/ImageBuffer.h>
#include <graphics/Renderer.h>
#include <graphics/RenderEvent.h>
#include <system/System.h>
#include <ui/KeyEvent.h>
#include <ui/Mouse.h>
#include <ui/MouseCursor.h>
#include <ui/MouseEvent.h>
#include <ui/TouchEvent.h>
#include <ui/Window.h>
#include <ui/WindowEvent.h>
#include <utils/JNI.h>
#include <vm/NekoVM.h>


namespace lime {
	
	
	value lime_application_create (value callback) {
		
		Application* app = CreateApplication ();
		Application::callback = new AutoGCRoot (callback);
		return alloc_float ((intptr_t)app);
		
	}
	
	
	value lime_application_exec (value application) {
		
		Application* app = (Application*)(intptr_t)val_float (application);
		return alloc_int (app->Exec ());
		
	}
	
	
	value lime_application_init (value application) {
		
		Application* app = (Application*)(intptr_t)val_float (application);
		app->Init ();
		return alloc_null ();
		
	}
	
	
	value lime_application_get_ticks (value application) {
		
		return alloc_float (Application::GetTicks ());
		
	}
	
	
	value lime_application_quit (value application) {
		
		Application* app = (Application*)(intptr_t)val_float (application);
		return alloc_int (app->Quit ());
		
	}
	
	
	value lime_application_update (value application) {
		
		Application* app = (Application*)(intptr_t)val_float (application);
		return alloc_bool (app->Update ());
		
	}
	
	
	value lime_audio_load (value data) {
		
		AudioBuffer audioBuffer;
		Resource resource;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			ByteArray bytes (data);
			resource = Resource (&bytes);
			
		}
		
		if (WAV::Decode (&resource, &audioBuffer)) {
			
			return audioBuffer.Value ();
			
		}
		
		#ifdef LIME_OGG
		if (OGG::Decode (&resource, &audioBuffer)) {
			
			return audioBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_font_create_image (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		ImageBuffer image;
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		value data = alloc_empty_object ();
		alloc_field (data, val_id ("glyphs"), font->RenderToImage (&image));
		alloc_field (data, val_id ("image"), image.Value ());
		return data;
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	void lime_font_destroy (value fontHandle) {
		
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		delete font;
		font = 0;
		
	}
	
	
	value lime_font_get_family_name (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		return font->GetFamilyName ();
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_load (value fontFace) {
		
		#ifdef LIME_FREETYPE
		Font *font = Font::FromFile (val_string (fontFace));
		if (font) {

			value v = alloc_float ((intptr_t)font);
			val_gc (v, lime_font_destroy);
			return v;

		} else {

			return alloc_null ();

		}
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_load_glyphs (value fontHandle, value size, value glyphs) {
		
		#ifdef LIME_FREETYPE
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		font->SetSize (val_int (size));
		font->LoadGlyphs (val_string (glyphs));
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_font_load_range (value fontHandle, value size, value start, value end) {
		
		#ifdef LIME_FREETYPE
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		font->SetSize (val_int (size));
		font->LoadRange (val_int (start), val_int (end));
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_font_outline_decompose (value fontHandle, value size) {
		
		#ifdef LIME_FREETYPE
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		return font->Decompose (val_int (size));
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_image_encode (value buffer, value type, value quality) {
		
		ImageBuffer imageBuffer = ImageBuffer (buffer);
		ByteArray data;
		
		switch (val_int (type)) {
			
			case 0: 
				
				#ifdef LIME_PNG
				if (PNG::Encode (&imageBuffer, &data)) {
					
					//delete imageBuffer.data;
					return data.mValue;
					
				}
				#endif
				break;
			
			case 1:
				
				#ifdef LIME_JPEG
				if (JPEG::Encode (&imageBuffer, &data, val_int (quality))) {
					
					//delete imageBuffer.data;
					return data.mValue;
					
				}
				#endif
				break;
			
			default: break;
			
		}
		
		//delete imageBuffer.data;
		return alloc_null ();
		
	}
	
	
	value lime_image_load (value data) {
		
		ImageBuffer imageBuffer;
		Resource resource;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			ByteArray bytes (data);
			resource = Resource (&bytes);
			
		}
		
		#ifdef LIME_PNG
		if (PNG::Decode (&resource, &imageBuffer)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		#ifdef LIME_JPEG
		if (JPEG::Decode (&resource, &imageBuffer)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_jni_getenv () {
		
		#ifdef ANDROID
		return alloc_float ((intptr_t)JNI::GetEnv ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_key_event_manager_register (value callback, value eventObject) {
		
		KeyEvent::callback = new AutoGCRoot (callback);
		KeyEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_lzma_decode (value input_value) {
		
		/*buffer input_buffer = val_to_buffer(input_value);
		buffer output_buffer = alloc_buffer_len(0);
		
		Lzma::Decode (input_buffer, output_buffer);
		
		return buffer_val (output_buffer);*/
		return alloc_null ();
		
	}
	
	
	value lime_lzma_encode (value input_value) {
		
		/*buffer input_buffer = val_to_buffer(input_value);
		buffer output_buffer = alloc_buffer_len(0);
		
		Lzma::Encode (input_buffer, output_buffer);
		
		return buffer_val (output_buffer);*/
		return alloc_null ();
		
	}
	
	
	value lime_mouse_event_manager_register (value callback, value eventObject) {
		
		MouseEvent::callback = new AutoGCRoot (callback);
		MouseEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_mouse_hide () {
		
		Mouse::Hide ();
		return alloc_null ();
		
	}
	
	
	value lime_mouse_set_cursor (value cursor) {
		
		Mouse::SetCursor ((MouseCursor)val_int (cursor));
		return alloc_null ();
		
	}
	
	
	value lime_mouse_show () {
		
		Mouse::Show ();
		return alloc_null ();
		
	}
	
	
	value lime_neko_execute (value module) {
		
		#ifdef LIME_NEKO
		NekoVM::Execute (val_string (module));
		#endif
		return alloc_null ();
		
	}
	
	
	value lime_render_event_manager_register (value callback, value eventObject) {
		
		RenderEvent::callback = new AutoGCRoot (callback);
		RenderEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_renderer_create (value window) {
		
		Renderer* renderer = CreateRenderer ((Window*)(intptr_t)val_float (window));
		return alloc_float ((intptr_t)renderer);
		
	}
	
	
	value lime_renderer_flip (value renderer) {
		
		((Renderer*)(intptr_t)val_float (renderer))->Flip ();
		return alloc_null (); 
		
	}
	
	
	value lime_system_gettimer () {
		
		return alloc_float (System::GetTimer ());
		
	}
	
	
	void lime_text_destroy (value textHandle) {
		
		#ifdef LIME_HARFBUZZ
		Text *text = (Text*)(intptr_t)val_float (textHandle);
		delete text;
		text = 0;
		#endif
		
	}
	
	
	value lime_text_create (value direction, value script, value language) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		Text *text = new Text (val_int (direction), val_string (script), val_string (language));
		value v = alloc_float ((intptr_t)text);
		val_gc (v, lime_text_destroy);
		return v;
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_text_from_string (value textHandle, value fontHandle, value size, value textString) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		Text *text = (Text*)(intptr_t)val_float (textHandle);
		Font *font = (Font*)(intptr_t)val_float (fontHandle);
		return text->FromString(font, val_int (size), val_string (textString));
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_touch_event_manager_register (value callback, value eventObject) {
		
		TouchEvent::callback = new AutoGCRoot (callback);
		TouchEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_update_event_manager_register (value callback, value eventObject) {
		
		UpdateEvent::callback = new AutoGCRoot (callback);
		UpdateEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_window_close (value window) {
		
		Window* targetWindow = (Window*)(intptr_t)val_float (window);
		targetWindow->Close ();
		delete targetWindow;
		return alloc_null ();
		
	}
	
	
	value lime_window_create (value application, value width, value height, value flags, value title) {
		
		Window* window = CreateWindow ((Application*)(intptr_t)val_float (application), val_int (width), val_int (height), val_int (flags), val_string (title));
		return alloc_float ((intptr_t)window);
		
	}
	
	
	value lime_window_event_manager_register (value callback, value eventObject) {
		
		WindowEvent::callback = new AutoGCRoot (callback);
		WindowEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_window_move (value window, value x, value y) {
		
		Window* targetWindow = (Window*)(intptr_t)val_float (window);
		targetWindow->Move (val_int (x), val_int (y));
		return alloc_null ();
		
	}
	
	
	value lime_window_resize (value window, value width, value height) {
		
		Window* targetWindow = (Window*)(intptr_t)val_float (window);
		targetWindow->Resize (val_int (width), val_int (height));
		return alloc_null ();
		
	}
	
	
	value lime_window_set_icon (value window, value buffer) {
		
		Window* targetWindow = (Window*)(intptr_t)val_float (window);
		ImageBuffer imageBuffer = ImageBuffer (buffer);
		targetWindow->SetIcon (&imageBuffer);
		return alloc_null ();
		
	}
	
	
	DEFINE_PRIM (lime_application_create, 1);
	DEFINE_PRIM (lime_application_exec, 1);
	DEFINE_PRIM (lime_application_init, 1);
	DEFINE_PRIM (lime_application_get_ticks, 0);
	DEFINE_PRIM (lime_application_quit, 1);
	DEFINE_PRIM (lime_application_update, 1);
	DEFINE_PRIM (lime_audio_load, 1);
	DEFINE_PRIM (lime_font_create_image, 1);
	DEFINE_PRIM (lime_font_get_family_name, 1);
	DEFINE_PRIM (lime_font_load, 1);
	DEFINE_PRIM (lime_font_load_glyphs, 3);
	DEFINE_PRIM (lime_font_load_range, 4);
	DEFINE_PRIM (lime_font_outline_decompose, 2);
	DEFINE_PRIM (lime_image_encode, 3);
	DEFINE_PRIM (lime_image_load, 1);
	DEFINE_PRIM (lime_jni_getenv, 0);
	DEFINE_PRIM (lime_key_event_manager_register, 2);
	DEFINE_PRIM (lime_lzma_encode, 1);
	DEFINE_PRIM (lime_lzma_decode, 1);
	DEFINE_PRIM (lime_mouse_hide, 0);
	DEFINE_PRIM (lime_mouse_set_cursor, 1);
	DEFINE_PRIM (lime_mouse_show, 0);
	DEFINE_PRIM (lime_mouse_event_manager_register, 2);
	DEFINE_PRIM (lime_neko_execute, 1);
	DEFINE_PRIM (lime_renderer_create, 1);
	DEFINE_PRIM (lime_renderer_flip, 1);
	DEFINE_PRIM (lime_render_event_manager_register, 2);
	DEFINE_PRIM (lime_system_gettimer, 0);
	DEFINE_PRIM (lime_text_create, 3);
	DEFINE_PRIM (lime_text_from_string, 4);
	DEFINE_PRIM (lime_touch_event_manager_register, 2);
	DEFINE_PRIM (lime_update_event_manager_register, 2);
	DEFINE_PRIM (lime_window_close, 1);
	DEFINE_PRIM (lime_window_create, 5);
	DEFINE_PRIM (lime_window_event_manager_register, 2);
	DEFINE_PRIM (lime_window_move, 3);
	DEFINE_PRIM (lime_window_resize, 3);
	DEFINE_PRIM (lime_window_set_icon, 2);
	
	
}


extern "C" int lime_register_prims () {
	
	return 0;
	
}
