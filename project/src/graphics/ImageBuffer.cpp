#include <graphics/ImageBuffer.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {
	
	struct ImageBufferId {

		ImageBufferId () {

			init = false;

		}

		int bitsPerPixel;
		int bpp;
		int buffer;
		int data;
		int format;
		int height;
		int width;
		int transparent;
		bool init;

	};
	
	static ThreadLocalStorage<ImageBufferId> stringId;

	static void initializeId (ImageBufferId &id) {

		id.bpp = val_id ("bpp");
		id.bitsPerPixel = val_id ("bitsPerPixel");
		id.transparent = val_id ("transparent");
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
		bpp = 4;
		format = RGBA;
		data = 0;
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
		bpp = val_int (val_field (imageBuffer, id.bitsPerPixel));
		format = (PixelFormat)val_int (val_field (imageBuffer, id.format));
		transparent = val_bool (val_field (imageBuffer, id.transparent));
		value data_value = val_field (imageBuffer, id.data);
		value buffer_value = val_field (data_value, id.buffer);
		
		//if (val_is_buffer (buffer_value))
			data = new ByteArray (buffer_value);
		//else
			//data = new ByteArray (data_value);
		
	}
	
	
	ImageBuffer::~ImageBuffer () {
		
		delete data;
		
	}
	
	
	void ImageBuffer::Blit (const unsigned char *data, int x, int y, int width, int height) {
		
		if (x < 0 || x + width > this->width || y < 0 || y + height > this->height) {
			
			return;
			
		}
		
		unsigned char *bytes = this->data->Bytes ();
		
		for (int i = 0; i < height; i++) {
			
			memcpy (&bytes[(i + y) * this->width + x], &data[i * width], width * bpp);
			
		}
		
	}
	
	
	void ImageBuffer::Resize (int width, int height, int bpp) {
		
		this->bpp = bpp;
		this->width = width;
		this->height = height;
		if (this->data) delete this->data;
		this->data = new ByteArray (width * height * bpp);
		
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
		alloc_field (mValue, id.bpp, alloc_int (bpp));
		alloc_field (mValue, id.transparent, alloc_bool (transparent));
		alloc_field (mValue, id.data, data->mValue);
		alloc_field (mValue, id.format, alloc_int (format));
		return mValue;
		
	}
	
	
}