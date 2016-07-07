#ifndef LIME_UTILS_POINTER_CONVERTER_H
#define LIME_UTILS_POINTER_CONVERTER_H

#include <hx/CFFI.h>

namespace lime {
	
	value Window_to_value(Window *inInstance);

	Window* val_to_Window(value inHandle);
	
}

#endif