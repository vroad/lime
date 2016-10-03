#include <utils/ArrayBufferView.h>
#include <utils/StringId.h>
#include <assert.h>


namespace lime {
	
	
	ArrayBufferView::ArrayBufferView () {
		
		_value = 0;
		byteOffset = 0;
		byteLength = 0;
		
	}
	
	
	ArrayBufferView::ArrayBufferView (int size) {
		
		data.reset (new Bytes (size));
		byteOffset = 0;
		byteLength = size;
		_value = 0;
		
	}
	
	
	ArrayBufferView::ArrayBufferView (value inValue) {
		
		Set (inValue);
		
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
	
	
	void ArrayBufferView::Resize (int size) {
		
		assert (data);
		
		data->Resize (size);
		byteLength = size;
		
	}
	
	
	value ArrayBufferView::Value () {
		
		if (val_is_null (_value)) {
			
			_value = alloc_empty_object ();
			
		}
		
		StringId* id = StringId::Get ();
		
		alloc_field (_value, id->buffer, data ? data->Value () : alloc_null ());
		alloc_field (_value, id->byteLength, alloc_int (byteLength));
		alloc_field (_value, id->length, alloc_int (byteLength));
		return _value;
		
	}
	
	
}