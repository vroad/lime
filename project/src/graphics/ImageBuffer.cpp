#include <graphics/ImageBuffer.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {
	
	struct ImageBufferId {

		ImageBufferId () {

			init = false;

		}

		int bitsPerPixel;
		int buffer;
		int data;
		int format;
		int height;
		int premultiplied;
		int transparent;
		int width;
		bool init;

	};
	
	static ThreadLocalStorage<ImageBufferId> stringId;

	static void initializeId (ImageBufferId &id) {
		
		id.bitsPerPixel = val_id ("bitsPerPixel");
		id.transparent = val_id ("transparent");
		id.premultiplied = val_id ("premultiplied");
		id.buffer = val_id ("buffer");
		id.width = val_id ("width");
		id.height = val_id ("height");
		id.data = val_id ("data");
		id.format = val_id ("format");
		id.init = true;

	}



	ImageBuffer::ImageBuffer () {
		
		width = 0;
		height = 0;
		bitsPerPixel = 32;
		format = RGBA32;
		data = 0;
		premultiplied = false;
		transparent = false;
		
	}
	
	
	ImageBuffer::ImageBuffer (value imageBuffer) {
		
		ImageBufferId id = stringId.Get ();
		if (id.init == false) {
			
			initializeId (id);
			stringId.Set (id);
			
		}
		
		width = val_int (val_field (imageBuffer, id.width));
		height = val_int (val_field (imageBuffer, id.height));
		bitsPerPixel = val_int (val_field (imageBuffer, id.bitsPerPixel));
		format = (PixelFormat)val_int (val_field (imageBuffer, id.format));
		transparent = val_bool (val_field (imageBuffer, id.transparent));
		value data_value = val_field (imageBuffer, id.data);
		value buffer_value = val_field (data_value, id.buffer);
		premultiplied = val_bool (val_field (imageBuffer, id.premultiplied));
		data = new Bytes (buffer_value);
		
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
			
			this->data = new Bytes (height * stride);
			
		} else {
			
			this->data->Resize (height * stride);
			
		}
		
	}
	
	
	int ImageBuffer::Stride () {
		
		return width * (((bitsPerPixel + 3) & ~0x3) >> 3);
		
	}
	
	
	value ImageBuffer::Value () {
		
		ImageBufferId id = stringId.Get ();
		if (id.init == false) {
			
			initializeId (id);
			stringId.Set (id);

		}
		
		mValue = alloc_empty_object ();
		alloc_field (mValue, id.width, alloc_int (width));
		alloc_field (mValue, id.height, alloc_int (height));
		alloc_field (mValue, id.bitsPerPixel, alloc_int (bitsPerPixel));
		alloc_field (mValue, id.data, data->Value ());
		alloc_field (mValue, id.transparent, alloc_bool (transparent));
		alloc_field (mValue, id.format, alloc_int (format));
		alloc_field (mValue, id.premultiplied, alloc_bool (premultiplied));
		return mValue;
		
	}
	
	
}