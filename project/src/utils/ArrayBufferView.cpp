#include <utils/ArrayBufferView.h>
#include <utils/StringId.h>
#include <assert.h>


namespace lime {
	
	
	// TODO: ByteOffset?
	
	
	ArrayBufferView::ArrayBufferView () {
		
		byteLength = 0;
		length = 0;
		mValue = 0;
		
	}
	
	
	ArrayBufferView::ArrayBufferView (int size) {
		
		buffer.Resize (size);
		byteLength = size;
		length = size;
		mValue = 0;
		
	}
	
	
	ArrayBufferView::ArrayBufferView (value arrayBufferView) {
		
		Set (arrayBufferView);
		
	}
	
	
	ArrayBufferView::~ArrayBufferView () {
		
	}
	
	
	int ArrayBufferView::ByteLength () const {
		
		return byteLength;
		
	}
	
	
	void ArrayBufferView::Clear () {
		
		buffer.Clear ();
		byteLength = 0;
		length = 0;
		mValue = 0;
		
	}
	
	
	unsigned char *ArrayBufferView::Data () {
		
		return buffer.Data ();
		
	}
	
	
	const unsigned char *ArrayBufferView::Data () const {
		
		return buffer.Data ();
		
	}
	
	
	int ArrayBufferView::Length () const {
		
		return buffer.Length ();
		
	}
	
	
	void ArrayBufferView::Resize (int size) {
		
		buffer.Resize (size);
		byteLength = size;
		length = size;
		
	}
	
	
	void ArrayBufferView::Set (value arrayBufferView) {
		
		StringId* id = StringId::Get ();
		
		if (!val_is_null (arrayBufferView)) {
			
			buffer.Set (val_field (arrayBufferView, id->buffer));
			byteLength = val_int (val_field (arrayBufferView, id->byteLength));
			length = val_int (val_field (arrayBufferView, id->length));
			
		} else {
			
			buffer.Clear ();
			byteLength = 0;
			length = 0;
			
		}
		
		mValue = arrayBufferView;
		
	}
	
	
	void ArrayBufferView::Set (const QuickVec<unsigned char> data) {
		
		buffer.Set (data);
		byteLength = buffer.Length ();
		length = byteLength;
		
	}
	
	
	value ArrayBufferView::Value () {
		
		StringId* id = StringId::Get ();
		
		if (mValue == 0 || val_is_null (mValue)) {
			
			mValue = alloc_empty_object ();
			
		}
		
		alloc_field (mValue, id->buffer, buffer.Value ());
		alloc_field (mValue, id->byteLength, alloc_int (byteLength));
		alloc_field (mValue, id->length, alloc_int (length));
		return mValue;
		
	}
	
	
}