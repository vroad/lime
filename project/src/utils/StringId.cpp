#include <utils/StringId.h>
#include <hx/CFFI.h>

namespace lime
{
	
	std::unique_ptr<StringId> StringId::singleton;
	
	
	StringId::StringId () {
		
		//
		// ApplicationEvent
		//
		
		deltaTime = val_id ("deltaTime");
		type = val_id ("type");
		
		//
		// ArrayBufferView
		//
		
		buffer = val_id ("buffer");
		byteOffset = val_id ("byteOffset");
		byteLength = val_id ("byteLength");
		
		//
		// AudioBuffer
		//
		
		bitsPerSample = val_id ("bitsPerSample");
		channels = val_id ("channels");
		data = val_id ("data");
		sampleRate = val_id ("sampleRate");
		length = val_id ("length");
		
		//
		// Bytes
		//
		
		b = val_id ("b");
		length = val_id ("id");
		
		//
		// ColorMatrix
		//
		
		//buffer = val_id ("buffer");
		
		//
		// DropEvent
		//
		
		file = val_id ("file");
		type = val_id ("type");
		
		//
		// Font
		//
		
		//width = val_id ("width");
		//height = val_id ("height");
		//x = val_id ("x");
		//y = val_id ("y");
		offset = val_id ("offset");
		size = val_id ("size");
		codepoint = val_id ("codepoint");
		
		//buffer = val_id ("buffer");
		charCode = val_id ("charCode");
		horizontalAdvance = val_id ("horizontalAdvance");
		horizontalBearingX = val_id ("horizontalBearingX");
		horizontalBearingY = val_id ("horizontalBearingY");
		image = val_id ("image");
		index = val_id ("index");
		offsetX = val_id ("offsetX");
		offsetY = val_id ("offsetY");
		verticalAdvance = val_id ("verticalAdvance");
		verticalBearingX = val_id ("verticalBearingX");
		verticalBearingY = val_id ("verticalBearingY");
		
		//
		// GamepadEvent
		//
		
		axis = val_id ("axis");
		button = val_id ("button");
		id = val_id ("id");
		type = val_id ("type");
		value = val_id ("value");
		
		//
		// ImageBuffer
		//
		
		bitsPerPixel = val_id ("bitsPerPixel");
		transparent = val_id ("transparent");
		premultiplied = val_id ("premultiplied");
		buffer = val_id ("buffer");
		width = val_id ("width");
		height = val_id ("height");
		data = val_id ("data");
		format = val_id ("format");
		
		//
		// JoystickEvent
		//
		
		id = val_id ("id");
		index = val_id ("index");
		type = val_id ("type");
		value = val_id ("value");
		x = val_id ("x");
		y = val_id ("y");
		
		//
		// KeyEvent
		//
		
		keyCode = val_id ("keyCode");
		modifier = val_id ("modifier");
		type = val_id ("type");
		windowID = val_id ("windowID");
		
		//
		// SDLSystem
		//
		
		bounds = val_id ("bounds");
		currentMode = val_id ("currentMode");
		dpi = val_id ("dpi");
		height = val_id ("height");
		name = val_id ("name");
		pixelFormat = val_id ("pixelFormat");
		refreshRate = val_id ("refreshRate");
		supportedModes = val_id ("supportedModes");
		width = val_id ("width");
		
		//
		// TextEvent
		//
		
		length = val_id ("length");
		start = val_id ("start");
		text = val_id ("text");
		type = val_id ("type");
		windowID = val_id ("windowID");
		
		//
		// Image
		//
		
		buffer = val_id ("buffer");
		height = val_id ("height");
		offsetX = val_id ("offsetX");
		offsetY = val_id ("offsetY");
		width = val_id ("width");
		
		//
		// Matrix3
		//
		
		a = val_id ("a");
		b = val_id ("b");
		c = val_id ("c");
		d = val_id ("d");
		tx = val_id ("tx");
		ty = val_id ("ty");
		
		//
		// Rectangle
		//
		
		width = val_id ("width");
		height = val_id ("height");
		x = val_id ("x");
		y = val_id ("y");
		
		//
		// MouseEvent
		//
		
		button = val_id ("button");
		movementX = val_id ("movementX");
		movementY = val_id ("movementY");
		type = val_id ("type");
		windowID = val_id ("windowID");
		x = val_id ("x");
		y = val_id ("y");
		
		//
		// SensorEvent
		//
		
		id = val_id ("id");
		type = val_id ("type");
		x = val_id ("x");
		y = val_id ("y");
		z = val_id ("z");
		
		//
		// TextEvent
		//
		
		length = val_id ("length");
		start = val_id ("start");
		text = val_id ("text");
		type = val_id ("type");
		windowID = val_id ("windowID");
		
		//
		// TouchEvent
		//
		
		device = val_id ("device");
		dx = val_id ("dx");
		dy = val_id ("dy");
		id = val_id ("id");
		pressure = val_id ("pressure");
		type = val_id ("type");
		x = val_id ("x");
		y = val_id ("y");
		
		//
		// Vector2
		//
		
		x = val_id ("x");
		y = val_id ("y");
		
		//
		// WindowEvent
		//
		
		height = val_id ("height");
		type = val_id ("type");
		width = val_id ("width");
		windowID = val_id ("windowID");
		x = val_id ("x");
		y = val_id ("y");
		
	}
	
	StringId* StringId::Get () {
		
		if (!singleton) {
			
			singleton.reset (new StringId ());
			
		}
		
		return singleton.get ();
		
	}
	
	void StringId::Reset () {
		
		if (singleton) {
			
			singleton.reset (NULL);
			
		}
		
	}

}