#ifndef LIME_UTILS_STRING_ID_H
#define LIME_UTILS_STRING_ID_H

#include <memory>

namespace lime {

	class StringId {
	public:
		
		StringId ();
		
		static StringId *Get ();
		
		static void Reset ();
		
		//
		// ApplicationEvent
		//
		
		int deltaTime;
		int type;
		
		//
		// AudioBuffer
		//
		
		int bitsPerSample;
		int channels;
		int handle;
		int sourceData;
		int data;
		int sampleRate;
		int length;
		
		//
		// Bytes
		//
		
		int b;
		//int length;
		
		//
		// ColorMatrix
		//
		
		int buffer;
		
		//
		// DropEvent
		//
		
		int file;
		//int type;
		
		//
		// Font
		//
		
		//int buffer;
		int charCode;
		int codepoint;
		int height;
		int index;
		int horizontalAdvance;
		int horizontalBearingX;
		int horizontalBearingY;
		int image;
		int offset;
		int offsetX;
		int offsetY;
		int size;
		int verticalAdvance;
		int verticalBearingX;
		int verticalBearingY;
		int width;
		int x;
		int y;
		
		//
		// GamepadEvent
		//
		
		int axis;
		int button;
		int id;
		//int type;
		int value;
		
		//
		// ImageBuffer
		//
		
		int bitsPerPixel;
		//int buffer;
		//int data;
		int format;
		//int height;
		int premultiplied;
		int transparent;
		//int width;
		
		//
		// Matrix3
		//
		
		int a;
		//int b;
		int c;
		int d;
		int tx;
		int ty;
		
		//
		// SDLSystem
		//
		
		int bounds;
		int currentMode;
		int dpi;
		//int height;
		int name;
		int pixelFormat;
		int refreshRate;
		int supportedModes;
		//int width;
		
		//
		// Image
		//
		
		//int buffer;
		//int height;
		//int offsetX;
		//int offsetY;
		//int width;
		
		//
		// JoystickEvent
		//
		
		//int id;
		//int index;
		//int type;
		//int value;
		//int x;
		//int y;
		
		//
		// KeyEvent
		//
		
		int keyCode;
		int modifier;
		//int type;
		int windowID;
		
		//
		// MouseEvent
		//
		
		//int button;
		int movementX;
		int movementY;
		//int type;
		//int windowID;
		//int x;
		//int y;
		
		//
		// Rectangle
		//
		
		//int height;
		//int width;
		//int x;
		//int y;
		
		//
		// SensorEvent
		//
		
		//int id;
		//int type;
		//int x;
		//int y;
		int z;
		
		//
		// TextEvent
		//
		
		//int length;
		int start;
		int text;
		//int type;
		//int windowID;
		
		//
		// TouchEvent
		//
		
		int device;
		int dx;
		int dy;
		//int id;
		int pressure;
		//int type;
		//int x;
		//int y;
		
		//
		// Vector2
		//
		
		//int x;
		//int y;
		
		//
		// WindowEvent
		//
		
		//int height;
		//int type;
		//int width;
		//int windowID;
		//int x;
		//int y;
		
	private:
		
		static std::unique_ptr<StringId> singleton;
	};

}

#endif