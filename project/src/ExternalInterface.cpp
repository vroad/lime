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
#include <audio/AudioStream.h>
#include <graphics/format/JPEG.h>
#include <graphics/format/PNG.h>
#include <graphics/utils/ImageDataUtil.h>
#include <graphics/Image.h>
#include <graphics/ImageBuffer.h>
#include <graphics/Renderer.h>
#include <graphics/RenderEvent.h>
#include <system/System.h>
#include <text/Font.h>
#include <text/TextLayout.h>
#include <ui/Gamepad.h>
#include <ui/GamepadEvent.h>
#include <ui/KeyEvent.h>
#include <ui/Mouse.h>
#include <ui/MouseCursor.h>
#include <ui/MouseEvent.h>
#include <ui/TextEvent.h>
#include <ui/TouchEvent.h>
#include <ui/Window.h>
#include <ui/WindowEvent.h>
#include <utils/NativePointer.h>
#include <utils/JNI.h>
#include <vm/NekoVM.h>
#ifdef LIME_OGG
#include <vorbis/vorbisfile.h>
#endif

namespace lime {
	

	value lime_application_create (value callback) {
		
		Application* app = CreateApplication ();
		Application::callback = new AutoGCRoot (callback);
		NativePointer<Application> ptr (app);
		return ptr.mValue;
		
	}
	
	
	value lime_application_exec (value application) {
		
		NativePointer<Application> ptr (application);
		Application* app = ptr.mPointer;
		return alloc_int (app->Exec ());
		
	}
	
	
	value lime_application_init (value application) {
		
		NativePointer<Application> ptr (application);
		Application* app = ptr.mPointer;
		app->Init ();
		return alloc_null ();
		
	}
	
	
	value lime_application_quit (value application) {
		
		NativePointer<Application> ptr (application);
		Application* app = ptr.mPointer;
		return alloc_int (app->Quit ());
		
	}
	
	
	value lime_application_set_frame_rate (value application, value frameRate) {
		
		NativePointer<Application> ptr (application);
		Application* app = ptr.mPointer;
		app->SetFrameRate (val_number (frameRate));
		return alloc_null ();
		
	}
	
	
	value lime_application_update (value application) {
		
		NativePointer<Application> ptr (application);
		Application* app = ptr.mPointer;
		return alloc_bool (app->Update ());
		
	}
	
	
	value lime_audio_load (value data, value stream) {
		
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
		OggVorbis_File *oggFile = new OggVorbis_File ();
		if (OGG::Decode (&resource, &audioBuffer, oggFile, val_bool (stream))) {
			
			return audioBuffer.Value ();
			
		} else {
			
			delete oggFile;
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_audio_stream_decode (value handle, value sizeInBytes, value bufferCount) {
		
		NativePointer<AudioStream> ptr (handle);
		AudioStream *stream = ptr.mPointer;
		
		#ifdef LIME_OGG
		if (stream->format == OggFormat)
			return OGG::DecodeStream ((OggVorbis_File*)stream->handle, val_int (sizeInBytes), val_int (bufferCount));
		#endif 
		
		return alloc_null ();
	}
	
	
	value lime_font_get_ascender (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetAscender ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_descender (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetDescender ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_family_name (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_wstring (font->GetFamilyName ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_glyph_index (value fontHandle, value character) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetGlyphIndex ((char*)val_string (character)));
		#else
		return alloc_int (-1);
		#endif
		
	}
	
	
	value lime_font_get_glyph_indices (value fontHandle, value characters) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return font->GetGlyphIndices ((char*)val_string (characters));
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_glyph_metrics (value fontHandle, value index) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return font->GetGlyphMetrics (val_int (index));
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_height (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetHeight ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_num_glyphs (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetNumGlyphs ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_underline_position (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetUnderlinePosition ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_underline_thickness (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetUnderlineThickness ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_units_per_em (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return alloc_int (font->GetUnitsPerEM ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_load (value data) {
		
		#ifdef LIME_FREETYPE
		Resource resource;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			ByteArray bytes (data);
			resource = Resource (&bytes);
			
		}
		
		Font *font = new Font (&resource, 0);
		
		if (font) {
			
			if (font->face) {
				
				NativePointer<Font> ptr (font);
				return ptr.mValue;
				
			} else {
				
				delete font;
				
			}
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_font_outline_decompose (value fontHandle, value size) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		return font->Decompose (val_int (size));
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_render_glyph (value fontHandle, value index, value data) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		ByteArray bytes = ByteArray (data);
		return font->RenderGlyph (val_int (index), &bytes);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_render_glyphs (value fontHandle, value indices, value data) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		ByteArray bytes = ByteArray (data);
		return font->RenderGlyphs (indices, &bytes);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_set_size (value fontHandle, value fontSize) {
		
		#ifdef LIME_FREETYPE
		NativePointer<Font> ptr (fontHandle);
		Font *font = ptr.mPointer;
		font->SetSize (val_int (fontSize));
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_gamepad_event_manager_register (value callback, value eventObject) {
		
		GamepadEvent::callback = new AutoGCRoot (callback);
		GamepadEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_gamepad_get_device_guid (value id) {
		
		return alloc_string (Gamepad::GetDeviceGUID (val_int (id)));
		
	}
	
	
	value lime_gamepad_get_device_name (value id) {
		
		return alloc_string (Gamepad::GetDeviceName (val_int (id)));
		
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
	
	
	value lime_image_data_util_color_transform (value image, value rect, value colorMatrix) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		ColorMatrix _colorMatrix = ColorMatrix (colorMatrix);
		ImageDataUtil::ColorTransform (&_image, &_rect, &_colorMatrix);
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_copy_channel (value *arg, int nargs) {
		
		enum { image, sourceImage, sourceRect, destPoint, srcChannel, destChannel };
		
		Image _image = Image (arg[image]);
		Image _sourceImage = Image (arg[sourceImage]);
		Rectangle _sourceRect = Rectangle (arg[sourceRect]);
		Vector2 _destPoint = Vector2 (arg[destPoint]);
		ImageDataUtil::CopyChannel (&_image, &_sourceImage, &_sourceRect, &_destPoint, val_int (arg[srcChannel]), val_int (arg[destChannel]));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_copy_pixels (value image, value sourceImage, value sourceRect, value destPoint, value mergeAlpha) {
		
		Image _image = Image (image);
		Image _sourceImage = Image (sourceImage);
		Rectangle _sourceRect = Rectangle (sourceRect);
		Vector2 _destPoint = Vector2 (destPoint);
		ImageDataUtil::CopyPixels (&_image, &_sourceImage, &_sourceRect, &_destPoint, val_bool (mergeAlpha));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_fill_rect (value image, value rect, value color) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		ImageDataUtil::FillRect (&_image, &_rect, val_number (color));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_flood_fill (value image, value x, value y, value color) {
		
		Image _image = Image (image);
		ImageDataUtil::FloodFill (&_image, val_number (x), val_number (y), val_number (color));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_get_pixels (value image, value rect, value format) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		PixelFormat _format = (PixelFormat)val_int (format);
		ByteArray pixels = ByteArray ();
		ImageDataUtil::GetPixels (&_image, &_rect, _format, &pixels);
		return pixels.mValue;
		
	}
	
	
	value lime_image_data_util_merge (value *arg, int nargs) {
		
		enum { image, sourceImage, sourceRect, destPoint, redMultiplier, greenMultiplier, blueMultiplier, alphaMultiplier };
		
		Image _image = Image (arg[image]);
		Image _sourceImage = Image (arg[sourceImage]);
		Rectangle _sourceRect = Rectangle (arg[sourceRect]);
		Vector2 _destPoint = Vector2 (arg[destPoint]);
		ImageDataUtil::Merge (&_image, &_sourceImage, &_sourceRect, &_destPoint, val_int (arg[redMultiplier]), val_int (arg[greenMultiplier]), val_int (arg[blueMultiplier]), val_int (arg[alphaMultiplier]));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_multiply_alpha (value image) {
		
		Image _image = Image (image);
		ImageDataUtil::MultiplyAlpha (&_image);
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_resize (value image, value buffer, value width, value height) {
		
		Image _image = Image (image);
		ImageBuffer _buffer = ImageBuffer (buffer);
		ImageDataUtil::Resize (&_image, &_buffer, val_int (width), val_int (height));
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_set_format (value image, value format) {
		
		Image _image = Image (image);
		PixelFormat _format = (PixelFormat)val_int (format);
		ImageDataUtil::SetFormat (&_image, _format);
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_set_pixels (value image, value rect, value bytes, value format) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		ByteArray _bytes = ByteArray (bytes);
		PixelFormat _format = (PixelFormat)val_int (format);
		ImageDataUtil::SetPixels (&_image, &_rect, &_bytes, _format);
		return alloc_null ();
		
	}
	
	
	value lime_image_data_util_unmultiply_alpha (value image) {
		
		Image _image = Image (image);
		ImageDataUtil::UnmultiplyAlpha (&_image);
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
	
	
	value lime_mouse_warp (value x, value y, value window) {
		
		Window* windowRef = 0;
		
		if (!val_is_null (window)) {
			
			windowRef = (Window*)(intptr_t)val_float (window);
			
		}
		
		Mouse::Warp (val_int (x), val_int (y), windowRef);
		return alloc_null ();
		
	}
	
	
	value lime_mouse_set_lock (value lock) {
		
		Mouse::SetLock (val_bool (lock));
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
		
		NativePointer<Window> windowPtr (window);
		Renderer* renderer = CreateRenderer (windowPtr.mPointer);
		NativePointer<Renderer> ptr (renderer);
		return ptr.mValue;
		
	}
	
	
	value lime_renderer_flip (value renderer) {
		
		NativePointer<Renderer> ptr (renderer);
		ptr.mPointer->Flip ();
		return alloc_null (); 
		
	}
	
	
	value lime_renderer_lock (value renderer) {
		
		NativePointer<Renderer> ptr (renderer);
		return ptr.mPointer->Lock ();
		
	}
	
	
	value lime_renderer_unlock (value renderer) {
		
		NativePointer<Renderer> ptr (renderer);
		ptr.mPointer->Unlock ();
		return alloc_null ();
		
	}
	
	
	value lime_system_get_directory (value type, value company, value title) {
		
		const char* companyName = "";
		const char* titleName = "";
		
		if (!val_is_null (company)) companyName = val_string (company);
		if (!val_is_null (title)) titleName = val_string (title);
		
		const char* directory = System::GetDirectory ((SystemDirectory)val_int (type), companyName, titleName);
		
		if (directory) {
			
			return alloc_string (directory);
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	value lime_system_get_timer () {
		
		return alloc_float (System::GetTimer ());
		
	}
	
	
	value lime_text_event_manager_register (value callback, value eventObject) {
		
		TextEvent::callback = new AutoGCRoot (callback);
		TextEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_text_layout_create (value direction, value script, value language) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		
		TextLayout *text = new TextLayout (val_int (direction), val_string (script), val_string (language));
		NativePointer<TextLayout> ptr (text);
		return ptr.mValue;
		
		#else
		
		return alloc_null ();
		
		#endif
		
	}
	
	
	value lime_text_layout_position (value textHandle, value fontHandle, value size, value textString, value data) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		
		NativePointer<TextLayout> textPtr (textHandle);
		TextLayout *text = textPtr.mPointer;
		NativePointer<Font> fontPtr (fontHandle);
		Font *font = fontPtr.mPointer;
		ByteArray bytes = ByteArray (data);
		text->Position (font, val_int (size), val_string (textString), &bytes);
		
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_text_layout_set_direction (value textHandle, value direction) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		NativePointer<TextLayout> textPtr (textHandle);
		TextLayout *text = textPtr.mPointer;
		text->SetDirection (val_int (direction));
		#endif
		return alloc_null ();
		
	}
	
	
	value lime_text_layout_set_language (value textHandle, value direction) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		NativePointer<TextLayout> textPtr (textHandle);
		TextLayout *text = textPtr.mPointer;
		text->SetLanguage (val_string (direction));
		#endif
		return alloc_null ();
		
	}
	
	
	value lime_text_layout_set_script (value textHandle, value direction) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		NativePointer<TextLayout> textPtr (textHandle);
		TextLayout *text = textPtr.mPointer;
		text->SetScript (val_string (direction));
		#endif
		return alloc_null ();
		
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
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		targetWindow->Close ();
		return alloc_null ();
		
	}
	

	value lime_window_create (value application, value width, value height, value flags, value title) {
		
		NativePointer<Application> appPtr (application);
		Window* window = CreateWindow (appPtr.mPointer, val_int (width), val_int (height), val_int (flags), val_string (title));
		NativePointer<Window> ptr (window);
		return ptr.mValue;
		
	}
	
	
	value lime_window_event_manager_register (value callback, value eventObject) {
		
		WindowEvent::callback = new AutoGCRoot (callback);
		WindowEvent::eventObject = new AutoGCRoot (eventObject);
		return alloc_null ();
		
	}
	
	
	value lime_window_get_enable_text_events (value window) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_bool (targetWindow->GetEnableTextEvents ());
		
	}
	
	
	value lime_window_get_height (value window) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_int (targetWindow->GetHeight ());
		
	}
	
	
	value lime_window_get_width (value window) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_int (targetWindow->GetWidth ());
		
	}
	
	
	value lime_window_get_x (value window) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_int (targetWindow->GetX ());
		
	}
	
	
	value lime_window_get_y (value window) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_int (targetWindow->GetY ());
		
	}
	
	
	value lime_window_move (value window, value x, value y) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		targetWindow->Move (val_int (x), val_int (y));
		return alloc_null ();
		
	}
	
	
	value lime_window_resize (value window, value width, value height) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		targetWindow->Resize (val_int (width), val_int (height));
		return alloc_null ();
		
	}
	
	
	value lime_window_set_enable_text_events (value window, value enabled) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		targetWindow->SetEnableTextEvents (val_bool (enabled));
		return alloc_null ();
		
	}
	
	
	value lime_window_set_fullscreen (value window, value fullscreen) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_bool (targetWindow->SetFullscreen (val_bool (fullscreen)));
		
	}
	
	
	value lime_window_set_icon (value window, value buffer) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		ImageBuffer imageBuffer = ImageBuffer (buffer);
		targetWindow->SetIcon (&imageBuffer);
		return alloc_null ();
		
	}
	
	
	value lime_window_set_minimized (value window, value fullscreen) {
		
		NativePointer<Window> ptr (window);
		Window* targetWindow = ptr.mPointer;
		return alloc_bool (targetWindow->SetMinimized (val_bool (fullscreen)));
		
	}
	
	
	DEFINE_PRIM (lime_application_create, 1);
	DEFINE_PRIM (lime_application_exec, 1);
	DEFINE_PRIM (lime_application_init, 1);
	DEFINE_PRIM (lime_application_quit, 1);
	DEFINE_PRIM (lime_application_set_frame_rate, 2);
	DEFINE_PRIM (lime_application_update, 1);
	DEFINE_PRIM (lime_audio_load, 2);
	DEFINE_PRIM (lime_audio_stream_decode, 3);
	DEFINE_PRIM (lime_font_get_ascender, 1);
	DEFINE_PRIM (lime_font_get_descender, 1);
	DEFINE_PRIM (lime_font_get_family_name, 1);
	DEFINE_PRIM (lime_font_get_glyph_index, 2);
	DEFINE_PRIM (lime_font_get_glyph_indices, 2);
	DEFINE_PRIM (lime_font_get_glyph_metrics, 2);
	DEFINE_PRIM (lime_font_get_height, 1);
	DEFINE_PRIM (lime_font_get_num_glyphs, 1);
	DEFINE_PRIM (lime_font_get_underline_position, 1);
	DEFINE_PRIM (lime_font_get_underline_thickness, 1);
	DEFINE_PRIM (lime_font_get_units_per_em, 1);
	DEFINE_PRIM (lime_font_load, 1);
	DEFINE_PRIM (lime_font_outline_decompose, 2);
	DEFINE_PRIM (lime_font_render_glyph, 3);
	DEFINE_PRIM (lime_font_render_glyphs, 3);
	DEFINE_PRIM (lime_font_set_size, 2);
	DEFINE_PRIM (lime_gamepad_event_manager_register, 2);
	DEFINE_PRIM (lime_gamepad_get_device_guid, 1);
	DEFINE_PRIM (lime_gamepad_get_device_name, 1);
	DEFINE_PRIM (lime_image_data_util_color_transform, 3);
	DEFINE_PRIM_MULT (lime_image_data_util_copy_channel);
	DEFINE_PRIM (lime_image_data_util_copy_pixels, 5);
	DEFINE_PRIM (lime_image_data_util_fill_rect, 3);
	DEFINE_PRIM (lime_image_data_util_flood_fill, 4);
	DEFINE_PRIM (lime_image_data_util_get_pixels, 3);
	DEFINE_PRIM_MULT (lime_image_data_util_merge);
	DEFINE_PRIM (lime_image_data_util_multiply_alpha, 1);
	DEFINE_PRIM (lime_image_data_util_resize, 4);
	DEFINE_PRIM (lime_image_data_util_set_format, 2);
	DEFINE_PRIM (lime_image_data_util_set_pixels, 4);
	DEFINE_PRIM (lime_image_data_util_unmultiply_alpha, 1);
	DEFINE_PRIM (lime_image_encode, 3);
	DEFINE_PRIM (lime_image_load, 1);
	DEFINE_PRIM (lime_jni_getenv, 0);
	DEFINE_PRIM (lime_key_event_manager_register, 2);
	DEFINE_PRIM (lime_lzma_decode, 1);
	DEFINE_PRIM (lime_lzma_encode, 1);
	DEFINE_PRIM (lime_mouse_event_manager_register, 2);
	DEFINE_PRIM (lime_mouse_hide, 0);
	DEFINE_PRIM (lime_mouse_set_cursor, 1);
	DEFINE_PRIM (lime_mouse_set_lock, 1);
	DEFINE_PRIM (lime_mouse_show, 0);
	DEFINE_PRIM (lime_mouse_warp, 3);
	DEFINE_PRIM (lime_neko_execute, 1);
	DEFINE_PRIM (lime_renderer_create, 1);
	DEFINE_PRIM (lime_renderer_flip, 1);
	DEFINE_PRIM (lime_renderer_lock, 1);
	DEFINE_PRIM (lime_renderer_unlock, 1);
	DEFINE_PRIM (lime_render_event_manager_register, 2);
	DEFINE_PRIM (lime_system_get_directory, 3);
	DEFINE_PRIM (lime_system_get_timer, 0);
	DEFINE_PRIM (lime_text_event_manager_register, 2);
	DEFINE_PRIM (lime_text_layout_create, 3);
	DEFINE_PRIM (lime_text_layout_position, 5);
	DEFINE_PRIM (lime_text_layout_set_direction, 2);
	DEFINE_PRIM (lime_text_layout_set_language, 2);
	DEFINE_PRIM (lime_text_layout_set_script, 2);
	DEFINE_PRIM (lime_touch_event_manager_register, 2);
	DEFINE_PRIM (lime_update_event_manager_register, 2);
	DEFINE_PRIM (lime_window_close, 1);
	DEFINE_PRIM (lime_window_create, 5);
	DEFINE_PRIM (lime_window_event_manager_register, 2);
	DEFINE_PRIM (lime_window_get_enable_text_events, 1);
	DEFINE_PRIM (lime_window_get_height, 1);
	DEFINE_PRIM (lime_window_get_width, 1);
	DEFINE_PRIM (lime_window_get_x, 1);
	DEFINE_PRIM (lime_window_get_y, 1);
	DEFINE_PRIM (lime_window_move, 3);
	DEFINE_PRIM (lime_window_resize, 3);
	DEFINE_PRIM (lime_window_set_enable_text_events, 2);
	DEFINE_PRIM (lime_window_set_fullscreen, 2);
	DEFINE_PRIM (lime_window_set_icon, 2);
	DEFINE_PRIM (lime_window_set_minimized, 2);
	
	
}


extern "C" int lime_register_prims () {
	
	return 0;
	
}
