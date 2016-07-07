#include <utils/ArrayBufferView.h>
#include <utils/StringId.h>

namespace lime {
	
	ArrayBufferView::ArrayBufferView () {
		
		_value = NULL;
		byteOffset = 0;
		byteLength = 0;
		
	}
	
	bool ArrayBufferView::Set (value inValue) {
		
		_value = inValue;
		
		if (val_is_null (inValue)) {
			
			data.reset (NULL);
			byteOffset = 0;
			byteLength = 0;
			return false;
			
		}
		
		StringId* id = StringId::Get ();
		value inBytes = val_field (inValue, id->buffer);
		byteOffset = val_int (val_field (inValue, id->byteOffset));
		byteLength = val_int (val_field (inValue, id->byteLength));
		
		if (!data) {
			
			data.reset (new Bytes ());
			
		}
		
		if (!data->Set (inBytes)) {
			
			data.reset (NULL);
			byteOffset = 0;
			byteLength = 0;
			return false;
			
		}
		
		if (byteLength < 0 || (byteOffset + byteLength) > data->Length ()) {
			
			data.reset (NULL);
			byteOffset = 0;
			byteLength = 0;
			val_throw (alloc_string ("Invalid ArrayBufferView offset/length"));
			return false;
			
		}
		
		return true;
		
	}
	
	unsigned char* ArrayBufferView::Data () const {
		
		return data ? byteOffset + data->Data () : NULL;
		
	}
	
	int ArrayBufferView::ByteOffset () const {
		
		return byteOffset;
		
	}
	
	int ArrayBufferView::ByteLength () const {
		
		return byteLength;
		
	}
	
}