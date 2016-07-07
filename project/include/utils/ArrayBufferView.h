#ifndef LIME_UTILS_ARRAY_BUFFER_VIEW_H
#define LIME_UTILS_ARRAY_BUFFER_VIEW_H


#include <hx/CFFI.h>
#include <utils/Bytes.h>
#include <memory>

namespace lime {
	
	
	class ArrayBufferView {
		
		
	public:
		
		
		ArrayBufferView ();
		bool Set (value inValue);
		unsigned char* Data () const;
		int ByteOffset () const;
		int ByteLength () const;
		
	private:
		
		
		std::unique_ptr<Bytes> data;
		value _value;
		int byteOffset;
		int byteLength;
		
		
	};
	
	
}


#endif