#include <hx/CFFIExt.h>
#include <utils/Bytes.h>
#include <utils/StringId.h>

namespace lime {
	
	static bool useBufferInitialized = false;
	static bool useBuffer = false;
	
	inline void initialize () {
		
		if (!useBufferInitialized) {
			
			buffer b = alloc_buffer_len (1);
			
			if (buffer_data (b)) {
				
				useBuffer = true;
				
			}
			
			useBufferInitialized = true;
			
		}
		
	}
	
	
	Bytes::Bytes () {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		
	}
	
	
	Bytes::Bytes (int size) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		
		Resize (size);
		
	}
	
	
	Bytes::Bytes (value bytes) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		
		Set (bytes);
		
	}
	
	
	Bytes::Bytes (const char* path) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		
		ReadFile (path);
		
	}
	
	
	Bytes::Bytes (const QuickVec<unsigned char> data) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		
		Set (data);
		
	}
	
	
	Bytes::~Bytes () {
		
	}
	
	
	void Bytes::Clear () {
		
		_data = 0;
		_length = 0;
		_value = 0;
		
	}
	
	
	unsigned char *Bytes::Data () {
		
		return (unsigned char*)_data;
		
	}
	
	
	const unsigned char *Bytes::Data () const {
		
		return (const unsigned char*)_data;
		
	}
	
	
	int Bytes::Length () const {
		
		return _length;
		
	}
	
	
	value Bytes::Pin () {
		
		if (!HAS_pin_buffer ()) {
			
			return 0;
			
		}
		
		StringId *id = StringId::Get ();
		value b = val_field (_value, id->b);
		buffer buf = val_to_buffer (b);
		value pin = EXT_pin_buffer (buf);
		
		return pin;
		
	}
	
	
	int Bytes::ReadFile (const char* path) {
		
		FILE_HANDLE *file = lime::fopen (path, "rb");
		
		if (file) {
			
			int result = ReadFile (file);
			lime::fclose (file);
			return result;
			
		} else {
			
			return 0;
			
		}
		
	}
	
	
	int Bytes::ReadFile (FILE_HANDLE *file) {
		
		if (!file) {
			
			return 0;
			
		}
		
		lime::fseek (file, 0, SEEK_END);
		int size = lime::ftell (file);
		lime::fseek (file, 0, SEEK_SET);
		
		if (size > 0) {
			
			Resize (size);
			int status = lime::fread (_data, _length, 1, file);
			return status;
			
		} else {
			
			return 0;
			
		}
		
	}
	
	
	void Bytes::Resize (int size) {
		
		if (size != _length) {
			
			if (!_value) {
				
				_value = alloc_empty_object ();
				
			}
			
			StringId *id = StringId::Get ();
			
			if (val_is_null (val_field (_value, id->b))) {
				
				value dataValue;
				
				if (useBuffer) {
					
					buffer b = alloc_buffer_len (size);
					dataValue = buffer_val (b);
					_data = (unsigned char*)buffer_data (b);
					
				} else {
					
					dataValue = alloc_raw_string (size);
					_data = (unsigned char*)val_string (dataValue);
					
				}
				
				alloc_field (_value, id->b, dataValue);
				
			} else {
				
				if (useBuffer) {
					
					buffer b = val_to_buffer (val_field (_value, id->b));
					buffer_set_size (b, size);
					_data = (unsigned char*)buffer_data (b);
					
				} else {
					
					value s = alloc_raw_string (size);
					memcpy ((char *)val_string (s), val_string (val_field (_value, id->b)), _length);
					alloc_field (_value, id->b, s);
					_data = (unsigned char*)val_string (s);
					
				}
				
			}
			
			alloc_field (_value, id->length, alloc_int (size));
			
		}
		
		_length = size;
		
	}
	
	
	bool Bytes::Set (value bytes) {
		
		if (val_is_null (bytes)) {
			
			_length = 0;
			_data = 0;
			_value = 0;
			
		} else {
			
			StringId* id = StringId::Get ();
			_length = val_int (val_field (bytes, id->length));
			_value = bytes;
			
			if (_length > 0) {
				
				value b = val_field (bytes, id->b);
				
				if (val_is_string (b)) {
					
					_data = (unsigned char*)val_string (b);
					
				} else {
					
					cffiByteBuffer buf = val_to_buffer (b);
					_data = (unsigned char*)buffer_data (buf);
					int bufferSize = buffer_size (buf);
					
					if (_length > bufferSize) {
						
						val_throw (alloc_string ("Invalid bytes length"));
						return false;
						
					}
					
				}
				
			} else {
				
				_data = 0;
				return false;
				
			}
			
		}
		
		return true;
		
	}
	
	
	void Bytes::Set (const QuickVec<unsigned char> data) {
		
		int size = data.size ();
		
		if (size > 0) {
			
			Resize (size);
			memcpy (_data, &data[0], _length);
			
		} else {
			
			_data = 0;
			_length = 0;
			
		}
		
	}
	
	
	void Bytes::Unpin (value pin) {
		
		if (HAS_unpin_buffer ()) {
			
			EXT_unpin_buffer (pin);
			
		}
		
	}
	
	
	value Bytes::Value () {
		
		if (_value) {
			
			return _value;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
}