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
#include <system/CFFIPointer.h>
#include <system/Clipboard.h>
#include <system/JNI.h>
#include <system/Locale.h>
#include <system/SensorEvent.h>
#include <system/System.h>
#include <text/Font.h>
#include <text/TextLayout.h>
#include <ui/DropEvent.h>
#include <ui/FileDialog.h>
#include <ui/Gamepad.h>
#include <ui/GamepadEvent.h>
#include <ui/Haptic.h>
#include <ui/Joystick.h>
#include <ui/JoystickEvent.h>
#include <ui/KeyEvent.h>
#include <ui/MouseEvent.h>
#include <ui/TextEvent.h>
#include <ui/TouchEvent.h>
#include <ui/Window.h>
#include <ui/WindowEvent.h>

#include <utils/PointerWrapper.h>

#include <vm/NekoVM.h>
#ifdef LIME_OGG
#include <audio/OggAudioStream.h>
#endif
#ifdef LIME_VIDEO
#include <video/VideoLib.h>
#include <video/Video.h>
#endif

#include <utils/StringId.h>
#include <utils/GCRootUtils.h>

#include <graphics/OpenGLContext.h>
#include "graphics/opengl/OpenGLBindings.h"

#include <memory>


namespace lime {
	
	
	void lime_reset () {
		
		StringId::Reset ();
		removeAllGCRoot ();
		
	}
	
	
	value lime_audio_load (value data) {
		
		AudioBuffer audioBuffer;
		Resource resource;
		Bytes bytes;
		
		if (val_is_string (data)) {
			
			resource = Resource (val_string (data));
			
		} else {
			
			bytes = Bytes ();
			bytes.Set (data);
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
			
			std::unique_ptr<const char[]> text (Clipboard::GetText ());
			value _text = alloc_string (text.get ());
			return _text;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	void lime_clipboard_set_text (HxString text) {
		
		Clipboard::SetText (text.__s);
		
	}
	
	
	value lime_file_dialog_open_directory (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		std::unique_ptr<const char[]> path (FileDialog::OpenDirectory (filter.__s, defaultPath.__s));
		
		if (path) {
			
			value _path = alloc_string (path.get ());
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		#endif
		
		return 0;
		
	}
	
	value lime_file_dialog_open_file (HxString filter, HxString defaultPath) {
		
		#ifdef LIME_NFD
		std::unique_ptr<const char[]> path (FileDialog::OpenFile (filter.__s, defaultPath.__s));
		
		if (path) {
			
			value _path = alloc_string (path.get ());
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
		std::unique_ptr<const char[]> path (FileDialog::SaveFile (filter.__s, defaultPath.__s));
		
		if (path) {
			
			value _path = alloc_string (path.get ());
			return _path;
			
		} else {
			
			return alloc_null ();
			
		}
		#endif
		
		return 0;
		
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
	
	
	value lime_jpeg_decode_bytes (value data, bool decodeData) {
		
		ImageBuffer imageBuffer;
		
		Bytes bytes;
		bytes.Set (data);
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
	
	
	void lime_haptic_vibrate (int period, int duration) {
		
		#ifdef IPHONE
		Haptic::Vibrate (period, duration);
		#endif
		
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

	value lime_video_lib_create () {

		#ifdef LIME_VIDEO
		VideoLib *lib = CreateVideoLib ();
		return CFFIPointer (lib, lime_pointer_destroy<VideoLib>);
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_lib_create_video (value videoLib) {

		#ifdef LIME_VIDEO
		VideoLib *lib = (VideoLib*)val_data (videoLib);
		return CFFIPointer (lib->CreateVideo (), lime_pointer_destroy<VideoLib>);
		#else
		return alloc_null ();
		#endif

	}

	value lime_video_open_url (value inVideo, value url) {

		#ifdef LIME_VIDEO
		Video *video = (Video*)val_data (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_bool (video->OpenURL (val_wstring (url)));
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_get_state (value inVideo) {

		#ifdef LIME_VIDEO
		Video *video = (Video*)val_data (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_int (video->GetState ());
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_play (value inVideo) {

		#ifdef LIME_VIDEO
		Video *video = (Video*)val_data (inVideo);
		if (video == NULL) return alloc_null ();
		return alloc_bool (video->Play ());
		#else
		return alloc_null ();
		#endif

	}


	value lime_video_set_texture (value inVideo, value texture) {

		#ifdef LIME_VIDEO
		Video *video = (Video*)val_data (inVideo);
		if (video == NULL) return alloc_null ();
		video->SetTexture (val_int (texture));
		return alloc_null ();
		#else
		return alloc_null ();
		#endif

	}
	
	
	DEFINE_PRIME0v (lime_reset);
	DEFINE_PRIME1 (lime_audio_load);
	DEFINE_PRIME1 (lime_bytes_read_file);
	DEFINE_PRIME1 (lime_cffi_get_native_pointer);
	#if 0
	DEFINE_PRIME1 (lime_cffi_set_finalizer);
	#endif
	DEFINE_PRIME0 (lime_clipboard_get_text);
	DEFINE_PRIME1v (lime_clipboard_set_text);
	DEFINE_PRIME2 (lime_file_dialog_open_directory);
	DEFINE_PRIME2 (lime_file_dialog_open_file);
	DEFINE_PRIME2 (lime_file_dialog_open_files);
	DEFINE_PRIME2 (lime_file_dialog_save_file);
	DEFINE_PRIME2v (lime_haptic_vibrate);
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
	DEFINE_PRIME2 (lime_jpeg_decode_bytes);
	DEFINE_PRIME2 (lime_jpeg_decode_file);
	DEFINE_PRIME1v (lime_neko_execute);
	DEFINE_PRIME2 (lime_png_decode_bytes);
	DEFINE_PRIME2 (lime_png_decode_file);
	
	
}


#ifdef LIME_CAIRO
extern "C" int lime_cairo_register_prims ();
#else
extern "C" int lime_cairo_register_prims () { return 0; }
#endif

#ifdef LIME_CURL
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
