#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


//#include <hx/CFFIPrimePatch.h>
#include <hx/CFFIPrime.h>
#include <app/Application.h>
#include <app/ApplicationEvent.h>
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
#include <system/Clipboard.h>
#include <system/JNI.h>
#include <system/SensorEvent.h>
#include <system/System.h>
#include <text/Font.h>
#include <text/TextLayout.h>
#include <ui/DropEvent.h>
#include <ui/FileDialog.h>
#include <ui/Gamepad.h>
#include <ui/GamepadEvent.h>
#include <ui/Joystick.h>
#include <ui/JoystickEvent.h>
#include <ui/KeyEvent.h>
#include <ui/Mouse.h>
#include <ui/MouseCursor.h>
#include <ui/MouseEvent.h>
#include <ui/TextEvent.h>
#include <ui/TouchEvent.h>
#include <ui/Window.h>
#include <ui/WindowEvent.h>
#include <utils/PointerWrapper.h>
#ifdef LIME_LZMA
#include <utils/LZMA.h>
#endif
#include <vm/NekoVM.h>
#ifdef LIME_OGG
#include <audio/OggAudioStream.h>
#endif
#ifdef LIME_VIDEO
#include <video/VideoLib.h>
#include <video/Video.h>
#endif

#include <utils/Kinds.h>
#include <utils/SafeDelete.h>
#include <utils/GCRootUtils.h>

//DEFINE_KIND (k_finalizer);

namespace lime {
	
	static bool gQuit = false;
	
	template <>
	value WrapPointer<Application> (Application *app) {
		
		return WrapPointerInternal<Application> (app, GetKinds ().Application);
		
	}
	
	template <>
	value WrapPointer<Renderer> (Renderer *renderer) {
		
		return WrapPointerInternal<Renderer> (renderer, GetKinds ().Renderer);
		
	}
	
	template <>
	value WrapPointer<Font> (Font *font) {
		
		return WrapPointerInternal<Font> (font, GetKinds ().Font);
		
	}
	
	template <>
	value WrapPointer<TextLayout> (TextLayout *textLayout) {
		
		return WrapPointerInternal<TextLayout> (textLayout, GetKinds ().TextLayout);
		
	}

	template <>
	value WrapPointer<Window> (Window *window) {

		return WrapPointerInternal<Window> (window, GetKinds ().Window);

	}
	
	#ifdef LIME_VIDEO
	template <>
	value WrapPointer<VideoLib> (VideoLib *lib) {
		
		return WrapPointerInternal<VideoLib> (lib, GetKinds ().VideoLib);
		
	}
	#endif
	
	#ifdef LIME_VIDEO
	template <>
	value WrapPointer<Video> (Video *video) {
		
		return WrapPointerInternal<Video> (video, GetKinds ().Video);
		
	}
	#endif
	
	template <>
	Application *GetPointer<Application> (value handle) {
		
		return (Application*)val_to_kind (handle, GetKinds ().Application);
		
	}
	
	template <>
	AudioStream *GetPointer<AudioStream> (value handle) {
		
		return (AudioStream*)val_to_kind (handle, GetKinds ().AudioStream);
		
	}
	
	template <>
	Font *GetPointer<Font> (value handle) {
		
		return (Font*)val_to_kind (handle, GetKinds ().Font);
		
	}
	
	template <>
	Window *GetPointer<Window> (value handle) {
		
		return (Window*)val_to_kind (handle, GetKinds ().Window);
		
	}
	
	template <>
	Renderer *GetPointer<Renderer> (value handle) {
		
		return (Renderer*)val_to_kind (handle, GetKinds ().Renderer);
		
	}
	
	template <>
	TextLayout *GetPointer<TextLayout> (value handle) {
		
		return (TextLayout*)val_to_kind (handle, GetKinds ().TextLayout);
		
	}
	
	#ifdef LIME_VIDEO
	template <>
	VideoLib *GetPointer<VideoLib> (value handle) {
		
		return (VideoLib*)val_to_kind (handle, GetKinds ().VideoLib);
		
	}
	#endif
	
	#ifdef LIME_VIDEO
	template <>
	Video *GetPointer<Video> (value handle) {
		
		return (Video*)val_to_kind (handle, GetKinds ().Video);
		
	}
	#endif
	
	value RendererContext_to_value (void *context) {
		
		return WrapPointerInternal<void> (context, GetKinds ().RendererContext);
		
	}
	
	
	value lime_application_create (value callback) {
		
		Application* application = CreateApplication ();
		if (Application::callback == NULL)
			Application::callback = new AutoGCRoot (callback);
		else
			Application::callback->set (callback);
		return WrapPointerWithGC (application);
		
	}
	
	
	void lime_application_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (ApplicationEvent::callback == NULL)
			ApplicationEvent::callback = new AutoGCRoot (callback);
		else
			ApplicationEvent::callback->set (callback);
		
		if (ApplicationEvent::eventObject == NULL)
			ApplicationEvent::eventObject = new AutoGCRoot (eventObject);
		else
			ApplicationEvent::eventObject->set (eventObject);
		
	}
	
	
	int lime_application_exec (value application) {
		
		Application* app = GetPointer<Application> (application);
		if (app == NULL) return 0;
		return app->Exec ();
		
	}
	
	
	void lime_application_init (value application) {
		
		Application* app = GetPointer<Application> (application);
		if (app == NULL) return;
		app->Init ();
		
	}
	
	
	int lime_application_quit (value application) {
		
		Application* app = GetPointer<Application> (application);
		if (app == NULL) return 0;
		int result = app->Quit ();
		gQuit = true;
		
		SafeDelete (Application::callback);
		SafeDelete (ApplicationEvent::callback);
		SafeDelete (ApplicationEvent::eventObject);
		SafeDelete (GamepadEvent::callback);
		SafeDelete (GamepadEvent::eventObject);
		SafeDelete (KeyEvent::callback);
		SafeDelete (KeyEvent::eventObject);
		SafeDelete (MouseEvent::callback);
		SafeDelete (MouseEvent::eventObject);
		SafeDelete (RenderEvent::callback);
		SafeDelete (RenderEvent::eventObject);
		SafeDelete (SensorEvent::callback);
		SafeDelete (SensorEvent::eventObject);
		SafeDelete (TextEvent::callback);
		SafeDelete (TextEvent::eventObject);
		SafeDelete (TouchEvent::callback);
		SafeDelete (TouchEvent::eventObject);
		SafeDelete (WindowEvent::callback);
		SafeDelete (WindowEvent::eventObject);
		
		removeAllGCRoot ();
		
		return result;
		
	}
	
	
	void lime_application_set_frame_rate (value application, double frameRate) {
		
		Application* app = GetPointer<Application> (application);
		if (app == NULL) return;
		app->SetFrameRate (frameRate);
		
	}
	
	
	bool lime_application_update (value application) {
		
		Application* app = GetPointer<Application> (application);
		if (app == NULL) return false;
		return app->Update ();
		
	}
	
	
	value lime_audio_load (value data, bool stream) {
		
		AudioBuffer audioBuffer;
		Resource resource;
		Bytes bytes;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			bytes = Bytes (data);
			resource = Resource (&bytes);
			
		}
		
		if (WAV::Decode (&resource, &audioBuffer)) {
			
			return audioBuffer.Value ();
			
		}
		
		#ifdef LIME_OGG
		if (OGG::Decode (&resource, &audioBuffer, stream)) {
			
			return audioBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_audio_stream_decode (value handle, value sizeInBytes, value bufferCount) {
		
		AudioStream *stream = GetPointer<AudioStream> (handle);
		if (stream == NULL) return alloc_null ();
		
		#ifdef LIME_OGG
		if (stream->format == OggFormat) {
			OggAudioStream *oggStream = (OggAudioStream*)stream;
			return OGG::DecodeStream (oggStream->file, val_int (sizeInBytes), val_int (bufferCount));
		}
		#endif 
		
		return alloc_null ();
	}
	
	
	value lime_bytes_from_data_pointer (double data, int length) {
		
		#ifndef LIME_NO_RAW_POINTER_ACCESS
		intptr_t ptr = (intptr_t)data;
		Bytes bytes = Bytes (length);
		
		if (ptr) {
			
			memcpy (bytes.Data (), (const void*)ptr, length);
			
		}
		
		return bytes.Value ();
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	double lime_bytes_get_data_pointer (value bytes) {
		
		#ifndef LIME_NO_RAW_POINTER_ACCESS
		Bytes data = Bytes (bytes);
		return (intptr_t)data.Data ();
		#else
		return 0;
		#endif
		
	}
	
	
	value lime_bytes_read_file (HxString path) {
		
		Bytes data = Bytes (path.__s);
		return data.Value ();
		
	}
	
	
	double lime_cffi_get_native_pointer (value handle) {
		
		#ifndef LIME_NO_RAW_POINTER_ACCESS
		return (intptr_t)val_data (handle);
		#else
		return 0;
		#endif
		
	}
	
	
	#if 0
	void lime_cffi_finalizer (value abstract) {
		
		val_call0 ((value)val_data (abstract));
		
	}
	#endif
	
	
	#if 0
	value lime_cffi_set_finalizer (value callback) {
		
		value abstract = alloc_abstract (k_finalizer, callback);
		val_gc (abstract, lime_cffi_finalizer);
		return abstract;
		
	}
	#endif
	
	
	value lime_clipboard_get_text () {
		
		if (Clipboard::HasText ()) {
			
			const char* text = Clipboard::GetText ();
			value _text = alloc_string (text);
			
			// TODO: Should we free for all backends? (SDL requires it)
			
			free ((char*)text);
			return _text;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	void lime_clipboard_set_text (HxString text) {
		
		Clipboard::SetText (text.__s);
		
	}
	
	
	void lime_drop_event_manager_register (value callback, value eventObject) {
		
		DropEvent::callback = new AutoGCRoot (callback);
		DropEvent::eventObject = new AutoGCRoot (eventObject);
		
	}
	
	
	value lime_file_dialog_open_directory (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		const char* path = FileDialog::OpenDirectory (filter.__s, defaultPath.__s);
		
		if (path) {
			
			value _path = alloc_string (path);
			free ((char*) path);
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		#endif
		
		return 0;
		
	}
	
	value lime_file_dialog_open_file (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		const char* path = FileDialog::OpenFile (filter.__s, defaultPath.__s);
		
		if (path) {
			
			value _path = alloc_string (path);
			free ((char*) path);
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		#endif
		
		return 0;
		
	}
	
	
	value lime_file_dialog_open_files (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		std::vector<const char*> files;
		
		FileDialog::OpenFiles (&files, filter.__s, defaultPath.__s);
		value result = alloc_array (files.size ());
		
		for (int i = 0; i < files.size (); i++) {
			
			val_array_set_i (result, i, alloc_string (files[i]));
			free ((char*)files[i]);
			
		}
		#else
		value result = alloc_array (0);
		#endif
		
		return result;
		
	}
	
	
	value lime_file_dialog_save_file (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		const char* path = FileDialog::SaveFile (filter.__s, defaultPath.__s);
		
		if (path) {
			
			value _path = alloc_string (path);
			free ((char*) path);
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		#endif
		
		return 0;
		
	}
	
	
	int lime_font_get_ascender (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetAscender ();
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_font_get_descender (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetDescender ();
		#else
		return 0;
		#endif
		
	}
	
	
	value lime_font_get_family_name (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		wchar_t *name = font->GetFamilyName ();
		value result = alloc_wstring (name);
		delete name;
		return result;
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_font_get_glyph_index (value fontHandle, HxString character) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetGlyphIndex ((char*)character.__s);
		#else
		return -1;
		#endif
		
	}
	
	
	value lime_font_get_glyph_indices (value fontHandle, HxString characters) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return alloc_null ();
		return font->GetGlyphIndices ((char*)characters.__s);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_get_glyph_metrics (value fontHandle, int index) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return alloc_null ();
		return font->GetGlyphMetrics (index);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	int lime_font_get_height (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetHeight ();
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_font_get_num_glyphs (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetNumGlyphs ();
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	int lime_font_get_underline_position (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetUnderlinePosition ();
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_font_get_underline_thickness (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetUnderlineThickness ();
		#else
		return 0;
		#endif
		
	}
	
	
	int lime_font_get_units_per_em (value fontHandle) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return 0;
		return font->GetUnitsPerEM ();
		#else
		return 0;
		#endif
		
	}
	
	
	value lime_font_load (value data) {
		
		#ifdef LIME_FREETYPE
		Resource resource;
		Bytes bytes;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			bytes.Set (data);
			resource = Resource (&bytes);
			
		}
		
		Font *font = new Font (&resource, 0);
		
		if (font) {
			
			if (font->face) {
				
				return WrapPointerWithGC (font);
				
			} else {
				
				delete font;
				
			}
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_font_outline_decompose (value fontHandle, int size) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return alloc_null ();
		return font->Decompose (size);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_font_render_glyph (value fontHandle, int index, value data) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return alloc_null ();
		Bytes bytes = Bytes (data);
		return font->RenderGlyph (index, &bytes);
		#else
		return false;
		#endif
		
	}
	
	
	value lime_font_render_glyphs (value fontHandle, value indices, value data) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return alloc_null ();
		Bytes bytes = Bytes (data);
		return font->RenderGlyphs (indices, &bytes);
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	void lime_font_set_size (value fontHandle, int fontSize) {
		
		#ifdef LIME_FREETYPE
		Font *font = GetPointer<Font> (fontHandle);
		if (font == NULL) return;
		font->SetSize (fontSize);
		#endif
		
	}
	
	
	void lime_gamepad_add_mappings (value mappings) {
		
		int length = val_array_size (mappings);
		
		for (int i = 0; i < length; i++) {
			
			Gamepad::AddMapping (val_string (val_array_i (mappings, i)));
			
		}
		
	}
	
	
	void lime_gamepad_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (GamepadEvent::callback == NULL)
			GamepadEvent::callback = new AutoGCRoot (callback);
		else
			GamepadEvent::callback->set (callback);
		
		if (GamepadEvent::eventObject == NULL)
			GamepadEvent::eventObject = new AutoGCRoot (eventObject);
		else
			GamepadEvent::eventObject->set (eventObject);
		
	}
	
	
	value lime_gamepad_get_device_guid (int id) {
		
		const char* guid = Gamepad::GetDeviceGUID (id);
		return guid ? alloc_string (guid) : alloc_null ();
		
	}
	
	
	value lime_gamepad_get_device_name (int id) {
		
		const char* name = Gamepad::GetDeviceName (id);
		return name ? alloc_string (name) : alloc_null ();
		
	}
	
	
	value lime_image_encode (value buffer, int type, int quality) {
		
		ImageBuffer imageBuffer = ImageBuffer (buffer);
		Bytes data;
		
		switch (type) {
			
			case 0: 
				
				#ifdef LIME_PNG
				if (PNG::Encode (&imageBuffer, &data)) {
					
					//delete imageBuffer.data;
					return data.Value ();
					
				}
				#endif
				break;
			
			case 1:
				
				#ifdef LIME_JPEG
				if (JPEG::Encode (&imageBuffer, &data, quality)) {
					
					//delete imageBuffer.data;
					return data.Value ();
					
				}
				#endif
				break;
			
			default: break;
			
		}
		
		//delete imageBuffer.data;
		return alloc_null ();
		
	}
	
	
	value lime_image_load (value data) {
		
		ImageBuffer buffer;
		Resource resource;
		Bytes bytes;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			bytes.Set (data);
			resource = Resource (&bytes);
			
		}
		
		#ifdef LIME_PNG
		if (PNG::Decode (&resource, &buffer)) {
			
			return buffer.Value ();
			
		}
		#endif
		
		#ifdef LIME_JPEG
		if (JPEG::Decode (&resource, &buffer)) {
			
			return buffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	void lime_image_data_util_color_transform (value image, value rect, value colorMatrix) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		ColorMatrix _colorMatrix = ColorMatrix (colorMatrix);
		ImageDataUtil::ColorTransform (&_image, &_rect, &_colorMatrix);
		
	}
	
	
	void lime_image_data_util_copy_channel (value image, value sourceImage, value sourceRect, value destPoint, int srcChannel, int destChannel) {
		
		Image _image = Image (image);
		Image _sourceImage = Image (sourceImage);
		Rectangle _sourceRect = Rectangle (sourceRect);
		Vector2 _destPoint = Vector2 (destPoint);
		ImageDataUtil::CopyChannel (&_image, &_sourceImage, &_sourceRect, &_destPoint, srcChannel, destChannel);
		
	}
	
	
	void lime_image_data_util_copy_pixels (value image, value sourceImage, value sourceRect, value destPoint, value alphaImage, value alphaPoint, bool mergeAlpha) {
		
		Image _image = Image (image);
		Image _sourceImage = Image (sourceImage);
		Rectangle _sourceRect = Rectangle (sourceRect);
		Vector2 _destPoint = Vector2 (destPoint);
		
		if (val_is_null (alphaImage)) {
			
			ImageDataUtil::CopyPixels (&_image, &_sourceImage, &_sourceRect, &_destPoint, 0, 0, mergeAlpha);
			
		} else {
			
			Image _alphaImage = Image (alphaImage);
			Vector2 _alphaPoint = Vector2 (alphaPoint);
			
			ImageDataUtil::CopyPixels (&_image, &_sourceImage, &_sourceRect, &_destPoint, &_alphaImage, &_alphaPoint, mergeAlpha);
			
		}
		
	}
	
	
	void lime_image_data_util_fill_rect (value image, value rect, int rg, int ba) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		int32_t color = (rg << 16) | ba;
		ImageDataUtil::FillRect (&_image, &_rect, color);
		
	}
	
	
	void lime_image_data_util_flood_fill (value image, int x, int y, int rg, int ba) {
		
		Image _image = Image (image);
		int32_t color = (rg << 16) | ba;
		ImageDataUtil::FloodFill (&_image, x, y, color);
		
	}
	
	
	void lime_image_data_util_get_pixels (value image, value rect, int format, value bytes) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		PixelFormat _format = (PixelFormat)format;
		Bytes pixels = Bytes (bytes);
		ImageDataUtil::GetPixels (&_image, &_rect, _format, &pixels);
		
	}
	
	
	void lime_image_data_util_merge (value image, value sourceImage, value sourceRect, value destPoint, int redMultiplier, int greenMultiplier, int blueMultiplier, int alphaMultiplier) {
		
		Image _image = Image (image);
		Image _sourceImage = Image (sourceImage);
		Rectangle _sourceRect = Rectangle (sourceRect);
		Vector2 _destPoint = Vector2 (destPoint);
		ImageDataUtil::Merge (&_image, &_sourceImage, &_sourceRect, &_destPoint, redMultiplier, greenMultiplier, blueMultiplier, alphaMultiplier);
		
	}
	
	
	void lime_image_data_util_multiply_alpha (value image) {
		
		Image _image = Image (image);
		ImageDataUtil::MultiplyAlpha (&_image);
		
	}
	
	
	void lime_image_data_util_resize (value image, value buffer, int width, int height) {
		
		Image _image = Image (image);
		ImageBuffer _buffer = ImageBuffer (buffer);
		ImageDataUtil::Resize (&_image, &_buffer, width, height);
		
	}
	
	
	void lime_image_data_util_set_format (value image, int format) {
		
		Image _image = Image (image);
		PixelFormat _format = (PixelFormat)format;
		ImageDataUtil::SetFormat (&_image, _format);
		
	}
	
	
	void lime_image_data_util_set_pixels (value image, value rect, value bytes, int format) {
		
		Image _image = Image (image);
		Rectangle _rect = Rectangle (rect);
		Bytes _bytes = Bytes (bytes);
		PixelFormat _format = (PixelFormat)format;
		ImageDataUtil::SetPixels (&_image, &_rect, &_bytes, _format);
		
	}
	
	int lime_image_data_util_threshold (value image, value sourceImage, value sourceRect, value destPoint, int operation, int thresholdRG, int thresholdBA, int colorRG, int colorBA, int maskRG, int maskBA, bool copySource) {
		
		Image _image = Image (image);
		Image _sourceImage = Image (sourceImage);
		Rectangle _sourceRect = Rectangle (sourceRect);
		Vector2 _destPoint = Vector2 (destPoint);
		int32_t threshold = (thresholdRG << 16) | thresholdBA;
		int32_t color = (colorRG << 16) | colorBA;
		int32_t mask = (maskRG << 16) | maskBA;
		return ImageDataUtil::Threshold (&_image, &_sourceImage, &_sourceRect, &_destPoint, operation, threshold, color, mask, copySource);
		
	}
	
	void lime_image_data_util_unmultiply_alpha (value image) {
		
		Image _image = Image (image);
		ImageDataUtil::UnmultiplyAlpha (&_image);
		
	}
	
	
	void lime_joystick_event_manager_register (value callback, value eventObject) {
		
		JoystickEvent::callback = new AutoGCRoot (callback);
		JoystickEvent::eventObject = new AutoGCRoot (eventObject);
		
	}
	
	
	value lime_joystick_get_device_guid (int id) {
		
		const char* guid = Joystick::GetDeviceGUID (id);
		return guid ? alloc_string (guid) : alloc_null ();
		
	}
	
	
	value lime_joystick_get_device_name (int id) {
		
		const char* name = Joystick::GetDeviceName (id);
		return name ? alloc_string (name) : alloc_null ();
		
	}
	
	
	int lime_joystick_get_num_axes (int id) {
		
		return Joystick::GetNumAxes (id);
		
	}
	
	
	int lime_joystick_get_num_buttons (int id) {
		
		return Joystick::GetNumButtons (id);
		
	}
	
	
	int lime_joystick_get_num_hats (int id) {
		
		return Joystick::GetNumHats (id);
		
	}
	
	
	int lime_joystick_get_num_trackballs (int id) {
		
		return Joystick::GetNumTrackballs (id);
		
	}
	
	
	value lime_jpeg_decode_bytes (value data, bool decodeData) {
		
		ImageBuffer imageBuffer;
		
		Bytes bytes (data);
		Resource resource = Resource (&bytes);
		
		#ifdef LIME_JPEG
		if (JPEG::Decode (&resource, &imageBuffer, decodeData)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_jpeg_decode_file (HxString path, bool decodeData) {
		
		ImageBuffer imageBuffer;
		Resource resource = Resource (path.__s);
		
		#ifdef LIME_JPEG
		if (JPEG::Decode (&resource, &imageBuffer, decodeData)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	void lime_key_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (KeyEvent::callback == NULL)
			KeyEvent::callback = new AutoGCRoot (callback);
		else
			KeyEvent::callback->set (callback);
		
		if (KeyEvent::eventObject == NULL)
			KeyEvent::eventObject = new AutoGCRoot (eventObject);
		else
			KeyEvent::eventObject->set (eventObject);
		
	}
	
	
	value lime_lzma_decode (value buffer) {
		
		#ifdef LIME_LZMA
		Bytes data = Bytes (buffer);
		Bytes result;
		
		LZMA::Decode (&data, &result);
		
		return result.Value ();
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	value lime_lzma_encode (value buffer) {
		
		#ifdef LIME_LZMA
		Bytes data = Bytes (buffer);
		Bytes result;
		
		LZMA::Encode (&data, &result);
		
		return result.Value ();
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	void lime_mouse_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (MouseEvent::callback == NULL)
			MouseEvent::callback = new AutoGCRoot (callback);
		else
			MouseEvent::callback->set (callback);
		
		if (MouseEvent::eventObject == NULL)
			MouseEvent::eventObject = new AutoGCRoot (eventObject);
		else
			MouseEvent::eventObject->set (eventObject);
		
	}
	
	
	void lime_mouse_hide () {
		
		Mouse::Hide ();
		
	}
	
	
	void lime_mouse_set_cursor (int cursor) {
		
		Mouse::SetCursor ((MouseCursor)cursor);
		
	}
	
	
	void lime_mouse_set_lock (bool lock) {
		
		Mouse::SetLock (lock);
		
	}
	
	
	void lime_mouse_show () {
		
		Mouse::Show ();
		
	}
	
	
	void lime_mouse_warp (int x, int y, value window) {
		
		Window* windowRef = 0;
		
		if (!val_is_null (window)) {
			
			windowRef = GetPointer<Window> (window);
			
		}
		
		Mouse::Warp (x, y, windowRef);
		
	}
	
	
	void lime_neko_execute (HxString module) {
		
		#ifdef LIME_NEKO
		NekoVM::Execute (module.__s);
		#endif
		
	}
	
	
	value lime_png_decode_bytes (value data, bool decodeData) {
		
		ImageBuffer imageBuffer;
		
		Bytes bytes (data);
		Resource resource = Resource (&bytes);
		
		#ifdef LIME_PNG
		if (PNG::Decode (&resource, &imageBuffer, decodeData)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	value lime_png_decode_file (HxString path, bool decodeData) {
		
		ImageBuffer imageBuffer;
		Resource resource = Resource (path.__s);
		
		#ifdef LIME_PNG
		if (PNG::Decode (&resource, &imageBuffer, decodeData)) {
			
			return imageBuffer.Value ();
			
		}
		#endif
		
		return alloc_null ();
		
	}
	
	
	void lime_render_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (RenderEvent::callback == NULL)
			RenderEvent::callback = new AutoGCRoot (callback);
		else
			RenderEvent::callback->set (callback);
		
		if (RenderEvent::eventObject == NULL)
			RenderEvent::eventObject = new AutoGCRoot (eventObject);
		else
			RenderEvent::eventObject->set (eventObject);
		
	}
	
	
	value lime_renderer_create (value window) {
		
		Window *windowPtr = GetPointer<Window> (window);
		if (windowPtr == NULL) return alloc_null ();
		Renderer* renderer = CreateRenderer (windowPtr);
		return WrapPointerWithGC<Renderer> (renderer);
		
	}
	
	
	void lime_renderer_flip (value renderer) {
		
		Renderer *ptr = GetPointer<Renderer> (renderer);
		if (ptr == NULL) return;
		ptr->Flip ();
		
	}
	
	
	value lime_renderer_get_context (value renderer) {
		
		#ifndef LIME_NO_RAW_POINTER_ACCESS
		Renderer* targetRenderer = GetPointer<Renderer> (renderer);
		if (targetRenderer == NULL) return alloc_null ();
		return RendererContext_to_value (targetRenderer->GetContext ());
		#else
		return alloc_null ();
		#endif
		
	}
	
	
	double lime_renderer_get_scale (value renderer) {
		
		Renderer* targetRenderer = (Renderer*)val_data (renderer);
		return targetRenderer->GetScale ();
		
	}
	
	
	value lime_renderer_get_type (value renderer) {
		
		Renderer *targetRenderer = GetPointer<Renderer> (renderer);
		if (targetRenderer == NULL) return alloc_null ();
		const char* type = targetRenderer->Type ();
		return type ? alloc_string (type) : alloc_null ();
		
	}
	
	
	value lime_renderer_lock (value renderer) {
		
		Renderer *ptr = GetPointer<Renderer> (renderer);
		if (ptr == NULL) return alloc_null ();
		return ptr->Lock ();
		
	}
	
	
	void lime_renderer_make_current (value renderer) {
		
		Renderer *ptr = GetPointer<Renderer>(renderer);
		if (ptr == NULL) return;
		ptr->MakeCurrent ();
		
	}
	
	
	value lime_renderer_read_pixels (value renderer, value rect) {
		
		Renderer* targetRenderer = (Renderer*)val_data (renderer);
		ImageBuffer buffer;
		
		if (!val_is_null (rect)) {
			
			Rectangle _rect = Rectangle (rect);
			targetRenderer->ReadPixels (&buffer, &_rect);
			
		} else {
			
			targetRenderer->ReadPixels (&buffer, NULL);
			
		}
		
		return buffer.Value ();
		
	}
	
	
	void lime_renderer_unlock (value renderer) {
		
		Renderer *ptr = GetPointer<Renderer> (renderer);
		if (ptr == NULL) return;
		ptr->Unlock ();
		
	}
	
	
	void lime_sensor_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (SensorEvent::callback == NULL)
			SensorEvent::callback = new AutoGCRoot (callback);
		else
			SensorEvent::callback->set (callback);
		
		if (SensorEvent::eventObject == NULL)
			SensorEvent::eventObject = new AutoGCRoot (eventObject);
		else
			SensorEvent::eventObject->set (eventObject);
		
	}
	
	
	bool lime_system_get_allow_screen_timeout () {
		
		return System::GetAllowScreenTimeout ();
		
	}
	
	
	value lime_system_get_directory (int type, HxString company, HxString title) {
		
		const char* path = System::GetDirectory ((SystemDirectory)type, company.__s, title.__s);
		
		if (path) {
			
			value _path = alloc_string (path);
			free ((char*) path);
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	value lime_system_get_display (int id) {
		
		return System::GetDisplay (id);
		
	}
	
	
	int lime_system_get_num_displays () {
		
		return System::GetNumDisplays ();
		
	}
	
	
	double lime_system_get_timer () {
		
		return System::GetTimer ();
		
	}
	
	
	bool lime_system_set_allow_screen_timeout (bool allow) {
		
		return System::SetAllowScreenTimeout (allow);
		
	}
	
	
	void lime_text_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (TextEvent::callback == NULL)
			TextEvent::callback = new AutoGCRoot (callback);
		else
			TextEvent::callback->set (callback);
		
	}
	
	value lime_text_layout_create (int direction, HxString script, HxString language) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		
		TextLayout *text = new TextLayout (direction, script.__s, language.__s);
		return WrapPointerWithGC (text);
		
		#else
		
		return alloc_null ();
		
		#endif
		
	}
	
	
	value lime_text_layout_position (value textHandle, value fontHandle, int size, HxString textString, value data) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		
		TextLayout *text = GetPointer<TextLayout> (textHandle);
		Font *font = GetPointer<Font> (fontHandle);
		if (text == NULL || font == NULL) return alloc_null ();
		Bytes bytes = Bytes (data);
		text->Position (font, size, textString.__s, &bytes);
		return bytes.Value ();
		
		#endif
		
		return alloc_null ();
		
	}
	
	
	void lime_text_layout_set_direction (value textHandle, int direction) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		TextLayout *text = GetPointer<TextLayout> (textHandle);
		if (text == NULL) return;
		text->SetDirection (direction);
		#endif
		
	}
	
	
	void lime_text_layout_set_language (value textHandle, HxString language) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		TextLayout *text = GetPointer<TextLayout> (textHandle);
		if (text == NULL) return;
		text->SetLanguage (language.__s);
		#endif
		
	}
	
	
	void lime_text_layout_set_script (value textHandle, HxString script) {
		
		#if defined(LIME_FREETYPE) && defined(LIME_HARFBUZZ)
		TextLayout *text = GetPointer<TextLayout> (textHandle);
		if (text == NULL) return;
		text->SetScript (script.__s);
		#endif
		
	}
	
	
	void lime_touch_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (TouchEvent::callback == NULL)
			TouchEvent::callback = new AutoGCRoot (callback);
		else
			TouchEvent::callback->set (callback);
		
		if (TouchEvent::eventObject == NULL)
			TouchEvent::eventObject = new AutoGCRoot (eventObject);
		else
			TouchEvent::eventObject->set (eventObject);
		
	}
	
	
	void lime_window_alert (value window, HxString message, HxString title) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->Alert (message.__s, title.__s);
		
	}
	
	
	void lime_window_close (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->Close ();
		
	}
	
	
	value lime_window_create (value application, int width, int height, int flags, HxString title) {
		
		Application *appPtr = GetPointer<Application> (application);
		if (appPtr == NULL)
			return alloc_null ();
		Window* window = CreateWindow (appPtr, width, height, flags, title.__s);
		return WrapPointerWithGC (window);
		
	}
	
	
	void lime_window_event_manager_register (value callback, value eventObject) {
		
		if (gQuit) return;
		
		if (WindowEvent::callback == NULL)
			WindowEvent::callback = new AutoGCRoot (callback);
		else
			WindowEvent::callback->set (callback);
		
		if (WindowEvent::eventObject == NULL)
			WindowEvent::eventObject = new AutoGCRoot (eventObject);
		else
			WindowEvent::eventObject->set (eventObject);
		
	}
	
	
	void lime_window_focus (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->Focus ();
		
	}
	
	
	int lime_window_get_display (value window) {
		
		Window* targetWindow = (Window*)val_data (window);
		return targetWindow->GetDisplay ();
		
	}
	
	
	bool lime_window_get_enable_text_events (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return false;
		return targetWindow->GetEnableTextEvents ();
		
	}
	
	
	int lime_window_get_height (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return 0;
		return targetWindow->GetHeight ();
		
	}
	
	
	int32_t lime_window_get_id (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return 0;
		return (int32_t)targetWindow->GetID ();
		
	}
	
	
	int lime_window_get_width (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return 0;
		return targetWindow->GetWidth ();
		
	}
	
	
	int lime_window_get_x (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return 0;
		return targetWindow->GetX ();
		
	}
	
	
	int lime_window_get_y (value window) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return 0;
		return targetWindow->GetY ();
		
	}
	
	
	void lime_window_move (value window, int x, int y) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->Move (x, y);
		
	}
	
	
	void lime_window_resize (value window, int width, int height) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->Resize (width, height);
		
	}
	
	
	bool lime_window_set_borderless (value window, bool borderless) {
		
		Window* targetWindow = (Window*)val_data (window);
		return targetWindow->SetBorderless (borderless);
		
	}
	
	
	void lime_window_set_enable_text_events (value window, bool enabled) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		targetWindow->SetEnableTextEvents (enabled);
		
	}
	
	
	bool lime_window_set_fullscreen (value window, bool fullscreen) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return false;
		return targetWindow->SetFullscreen (fullscreen);
		
	}
	
	
	void lime_window_set_icon (value window, value buffer) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return;
		ImageBuffer imageBuffer = ImageBuffer (buffer);
		targetWindow->SetIcon (&imageBuffer);
		
	}
	
	
	bool lime_window_set_maximized (value window, bool maximized) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return false;
		return targetWindow->SetMaximized (maximized);
		
	}
	
	
	bool lime_window_set_minimized (value window, bool minimized) {
		
		Window* targetWindow = GetPointer<Window> (window);
		return targetWindow->SetMinimized (minimized);
		
	}
	
	
	bool lime_window_set_resizable (value window, bool resizable) {
		
		return targetWindow->SetResizable (resizable);
		
	}

	value lime_video_lib_create () {

		#ifdef LIME_VIDEO
		VideoLib *lib = CreateVideoLib ();
		return WrapPointerWithGC<VideoLib> (lib);
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_lib_create_video (value videoLib) {

		#ifdef LIME_VIDEO
		VideoLib *lib = GetPointer<VideoLib> (videoLib);
		return WrapPointerWithGC<Video> (lib->CreateVideo ());
		#else
		return alloc_null ();
		#endif

	}

	value lime_video_open_url (value inVideo, value url) {

		#ifdef LIME_VIDEO
		Video *video = GetPointer<Video> (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_bool (video->OpenURL (val_wstring (url)));
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_get_state (value inVideo) {

		#ifdef LIME_VIDEO
		Video *video = GetPointer<Video> (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_int (video->GetState ());
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_play (value inVideo) {

		#ifdef LIME_VIDEO
		Video *video = GetPointer<Video> (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_bool (video->Play ());
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_set_texture (value inVideo, value texture) {

		#ifdef LIME_VIDEO
		Video *video = GetPointer<Video> (inVideo);
		if (video == NULL) return alloc_null ();
		video->SetTexture (val_int (texture));
		return alloc_null ();
		#else
		return alloc_null ();
		#endif

	}
	
	value lime_window_set_title (value window, HxString title) {
		
		Window* targetWindow = GetPointer<Window> (window);
		if (targetWindow == NULL) return alloc_null ();
		const char* result = targetWindow->SetTitle (title.__s);
		
		if (result) {
			
			value _result = alloc_string (result);
			free ((char*) result);
			return _result;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	DEFINE_PRIME1 (lime_application_create);
	DEFINE_PRIME2v (lime_application_event_manager_register);
	DEFINE_PRIME1 (lime_application_exec);
	DEFINE_PRIME1v (lime_application_init);
	DEFINE_PRIME1 (lime_application_quit);
	DEFINE_PRIME2v (lime_application_set_frame_rate);
	DEFINE_PRIME1 (lime_application_update);
	DEFINE_PRIME2 (lime_audio_load);
	DEFINE_PRIME3 (lime_audio_stream_decode);
	DEFINE_PRIME2 (lime_bytes_from_data_pointer);
	DEFINE_PRIME1 (lime_bytes_get_data_pointer);
	DEFINE_PRIME1 (lime_bytes_read_file);
	DEFINE_PRIME1 (lime_cffi_get_native_pointer);
	#if 0
	DEFINE_PRIME1 (lime_cffi_set_finalizer);
	#endif
	DEFINE_PRIME0 (lime_clipboard_get_text);
	DEFINE_PRIME1v (lime_clipboard_set_text);
	DEFINE_PRIME2v (lime_drop_event_manager_register);
	DEFINE_PRIME2 (lime_file_dialog_open_directory);
	DEFINE_PRIME2 (lime_file_dialog_open_file);
	DEFINE_PRIME2 (lime_file_dialog_open_files);
	DEFINE_PRIME2 (lime_file_dialog_save_file);
	DEFINE_PRIME1 (lime_font_get_ascender);
	DEFINE_PRIME1 (lime_font_get_descender);
	DEFINE_PRIME1 (lime_font_get_family_name);
	DEFINE_PRIME2 (lime_font_get_glyph_index);
	DEFINE_PRIME2 (lime_font_get_glyph_indices);
	DEFINE_PRIME2 (lime_font_get_glyph_metrics);
	DEFINE_PRIME1 (lime_font_get_height);
	DEFINE_PRIME1 (lime_font_get_num_glyphs);
	DEFINE_PRIME1 (lime_font_get_underline_position);
	DEFINE_PRIME1 (lime_font_get_underline_thickness);
	DEFINE_PRIME1 (lime_font_get_units_per_em);
	DEFINE_PRIME1 (lime_font_load);
	DEFINE_PRIME2 (lime_font_outline_decompose);
	DEFINE_PRIME3 (lime_font_render_glyph);
	DEFINE_PRIME3 (lime_font_render_glyphs);
	DEFINE_PRIME2v (lime_font_set_size);
	DEFINE_PRIME1v (lime_gamepad_add_mappings);
	DEFINE_PRIME2v (lime_gamepad_event_manager_register);
	DEFINE_PRIME1 (lime_gamepad_get_device_guid);
	DEFINE_PRIME1 (lime_gamepad_get_device_name);
	DEFINE_PRIME3v (lime_image_data_util_color_transform);
	DEFINE_PRIME6v (lime_image_data_util_copy_channel);
	DEFINE_PRIME7v (lime_image_data_util_copy_pixels);
	DEFINE_PRIME4v (lime_image_data_util_fill_rect);
	DEFINE_PRIME5v (lime_image_data_util_flood_fill);
	DEFINE_PRIME4v (lime_image_data_util_get_pixels);
	DEFINE_PRIME8v (lime_image_data_util_merge);
	DEFINE_PRIME1v (lime_image_data_util_multiply_alpha);
	DEFINE_PRIME4v (lime_image_data_util_resize);
	DEFINE_PRIME2v (lime_image_data_util_set_format);
	DEFINE_PRIME4v (lime_image_data_util_set_pixels);
	DEFINE_PRIME12 (lime_image_data_util_threshold);
	DEFINE_PRIME1v (lime_image_data_util_unmultiply_alpha);
	DEFINE_PRIME3 (lime_image_encode);
	DEFINE_PRIME1 (lime_image_load);
	DEFINE_PRIME2v (lime_joystick_event_manager_register);
	DEFINE_PRIME1 (lime_joystick_get_device_guid);
	DEFINE_PRIME1 (lime_joystick_get_device_name);
	DEFINE_PRIME1 (lime_joystick_get_num_axes);
	DEFINE_PRIME1 (lime_joystick_get_num_buttons);
	DEFINE_PRIME1 (lime_joystick_get_num_hats);
	DEFINE_PRIME1 (lime_joystick_get_num_trackballs);
	DEFINE_PRIME2 (lime_jpeg_decode_bytes);
	DEFINE_PRIME2 (lime_jpeg_decode_file);
	DEFINE_PRIME2v (lime_key_event_manager_register);
	DEFINE_PRIME1 (lime_lzma_decode);
	DEFINE_PRIME1 (lime_lzma_encode);
	DEFINE_PRIME2v (lime_mouse_event_manager_register);
	DEFINE_PRIME0v (lime_mouse_hide);
	DEFINE_PRIME1v (lime_mouse_set_cursor);
	DEFINE_PRIME1v (lime_mouse_set_lock);
	DEFINE_PRIME0v (lime_mouse_show);
	DEFINE_PRIME3v (lime_mouse_warp);
	DEFINE_PRIME1v (lime_neko_execute);
	DEFINE_PRIME2 (lime_png_decode_bytes);
	DEFINE_PRIME2 (lime_png_decode_file);
	DEFINE_PRIME1 (lime_renderer_create);
	DEFINE_PRIME1v (lime_renderer_flip);
	DEFINE_PRIME1 (lime_renderer_get_context);
	DEFINE_PRIME1 (lime_renderer_get_scale);
	DEFINE_PRIME1 (lime_renderer_get_type);
	DEFINE_PRIME1 (lime_renderer_lock);
	DEFINE_PRIME1v (lime_renderer_make_current);
	DEFINE_PRIME2 (lime_renderer_read_pixels);
	DEFINE_PRIME1v (lime_renderer_unlock);
	DEFINE_PRIME2v (lime_render_event_manager_register);
	DEFINE_PRIME2v (lime_sensor_event_manager_register);
	DEFINE_PRIME0 (lime_system_get_allow_screen_timeout);
	DEFINE_PRIME3 (lime_system_get_directory);
	DEFINE_PRIME1 (lime_system_get_display);
	DEFINE_PRIME0 (lime_system_get_num_displays);
	DEFINE_PRIME0 (lime_system_get_timer);
	DEFINE_PRIME1 (lime_system_set_allow_screen_timeout);
	DEFINE_PRIME2v (lime_text_event_manager_register);
	DEFINE_PRIME3 (lime_text_layout_create);
	DEFINE_PRIME5 (lime_text_layout_position);
	DEFINE_PRIME2v (lime_text_layout_set_direction);
	DEFINE_PRIME2v (lime_text_layout_set_language);
	DEFINE_PRIME2v (lime_text_layout_set_script);
	DEFINE_PRIME2v (lime_touch_event_manager_register);
	DEFINE_PRIME3v (lime_window_alert);
	DEFINE_PRIME1v (lime_window_close);
	DEFINE_PRIME5 (lime_window_create);
	DEFINE_PRIME2v (lime_window_event_manager_register);
	DEFINE_PRIME1v (lime_window_focus);
	DEFINE_PRIME1 (lime_window_get_display);
	DEFINE_PRIME1 (lime_window_get_enable_text_events);
	DEFINE_PRIME1 (lime_window_get_height);
	DEFINE_PRIME1 (lime_window_get_id);
	DEFINE_PRIME1 (lime_window_get_width);
	DEFINE_PRIME1 (lime_window_get_x);
	DEFINE_PRIME1 (lime_window_get_y);
	DEFINE_PRIME3v (lime_window_move);
	DEFINE_PRIME3v (lime_window_resize);
	DEFINE_PRIME2 (lime_window_set_borderless);
	DEFINE_PRIME2v (lime_window_set_enable_text_events);
	DEFINE_PRIME2 (lime_window_set_fullscreen);
	DEFINE_PRIME2v (lime_window_set_icon);
	DEFINE_PRIME2 (lime_window_set_maximized);
	DEFINE_PRIME2 (lime_window_set_minimized);
	DEFINE_PRIME2 (lime_window_set_resizable);
	DEFINE_PRIME2 (lime_window_set_title);
	
	
}

#ifdef LIME_CAIRO
extern "C" int lime_cairo_register_prims ();
#else
extern "C" int lime_cairo_register_prims () { return 0; }
#endif

#ifdef LIME_CURL
#endif
extern "C" int lime_curl_register_prims ();
#else
extern "C" int lime_curl_register_prims () { return 0; }
#endif

#ifdef LIME_OPENAL
extern "C" int lime_openal_register_prims ();
#else
extern "C" int lime_openal_register_prims () { return 0; }
#endif

#ifdef LIME_OPENGL
extern "C" int lime_opengl_register_prims ();
#else
extern "C" int lime_opengl_register_prims () { return 0; }
#endif


extern "C" int lime_register_prims () {
	
	#ifdef LIME_CAIRO
	lime_cairo_register_prims ();
	#endif
	lime_curl_register_prims ();
	lime_openal_register_prims ();
	lime_opengl_register_prims ();
	
	return 0;
	
}
