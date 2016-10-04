#include <graphics/ImageBuffer.h>
#include <utils/StringId.h>

namespace lime {
	
	
	ImageBuffer::ImageBuffer () {
		
		width = 0;
		height = 0;
		bitsPerPixel = 32;
		format = RGBA32;
		data = 0;
		premultiplied = false;
		transparent = false;
		mValue = 0;
		
	}
	
	
	ImageBuffer::ImageBuffer (value imageBuffer) {
		
		StringId* id = StringId::Get ();
		
		if (!val_is_null (imageBuffer)) {
			
			width = val_int (val_field (imageBuffer, id->width));
			height = val_int (val_field (imageBuffer, id->height));
			bitsPerPixel = val_int (val_field (imageBuffer, id->bitsPerPixel));
			format = (PixelFormat)val_int (val_field (imageBuffer, id->format));
			transparent = val_bool (val_field (imageBuffer, id->transparent));
			premultiplied = val_bool (val_field (imageBuffer, id->premultiplied));
			data = new ArrayBufferView (val_field (imageBuffer, id->data));
			
		} else {
			
			width = 0;
			height = 0;
			bitsPerPixel = 32;
			format = RGBA32;
			data = 0;
			premultiplied = false;
			transparent = false;
			
		}
		
		mValue = imageBuffer;
		
	}
	
	
	ImageBuffer::~ImageBuffer () {
		
		delete data;
		
	}
	
	
	void ImageBuffer::Blit (const unsigned char *data, int x, int y, int width, int height) {
		
		if (x < 0 || x + width > this->width || y < 0 || y + height > this->height) {
			
			return;
			
		}
		
		int stride = Stride ();
		unsigned char *bytes = this->data->Data ();
		
		for (int i = 0; i < height; i++) {
			
			memcpy (&bytes[(i + y) * this->width + x], &data[i * width], stride);
			
		}
		
	}
	
	
	void ImageBuffer::Resize (int width, int height, int bitsPerPixel) {
		
		this->bitsPerPixel = bitsPerPixel;
		this->width = width;
		this->height = height;
		
		int stride = Stride ();
		
		if (!this->data) {
			
			this->data = new ArrayBufferView (height * stride);
			
		} else {
			
			this->data->Resize (height * stride);
			
		}
		
	}
	
	
	int ImageBuffer::Stride () {
		
		return width * (((bitsPerPixel + 3) & ~0x3) >> 3);
		
	}
	
	
	value ImageBuffer::Value () {
		
		if (!data) {
			
			return alloc_null ();
			
		}
		
		StringId* id = StringId::Get ();
		
		if (val_is_null (mValue)) {
			
			mValue = alloc_empty_object ();
			
		}
		
		alloc_field (mValue, id->width, alloc_int (width));
		alloc_field (mValue, id->height, alloc_int (height));
		alloc_field (mValue, id->bitsPerPixel, alloc_int (bitsPerPixel));
		alloc_field (mValue, id->data, data->Value ());
		alloc_field (mValue, id->transparent, alloc_bool (transparent));
		alloc_field (mValue, id->format, alloc_int (format));
		alloc_field (mValue, id->premultiplied, alloc_bool (premultiplied));
		return mValue;
		
	}
	
	
}