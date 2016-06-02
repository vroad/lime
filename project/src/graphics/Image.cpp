#include <graphics/Image.h>
#include <utils/StringId.h>

namespace lime {
	
	
	Image::Image () {
		
		buffer = 0;
		height = 0;
		offsetX = 0;
		offsetY = 0;
		width = 0;
		
	}
	
	
	Image::Image (value image) {
		
		StringId* id = StringId::Get ();
		
		width = val_int (val_field (image, id->width));
		height = val_int (val_field (image, id->height));
		buffer = new ImageBuffer (val_field (image, id->buffer));
		offsetX = val_int (val_field (image, id->offsetX));
		offsetY = val_int (val_field (image, id->offsetY));
		
	}
	
	
	Image::~Image () {
		
		delete buffer;
		
	}
	
	
}