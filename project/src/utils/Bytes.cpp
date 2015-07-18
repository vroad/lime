#include <system/System.h>
#include <utils/Bytes.h>
#include <utils/ThreadLocalStorage.h>

namespace lime {
	
	struct BytesId {

		BytesId () {

			init = false;

		}

		int b;
		int length;
		bool init;

	};
	
	static ThreadLocalStorage<BytesId> stringId;
	static bool useBufferInitialized = false;
	static bool useBuffer = false;
	
	inline void initialize () {

		BytesId id = stringId.Get ();
		
		if (!id.init) {
			
			id.b = val_id ("b");
			id.length = val_id ("length");
			
			buffer b = alloc_buffer_len (1);
			
			if (!useBufferInitialized) {

				if (buffer_data (b)) {
				
					useBuffer = true;
				
				}

				useBufferInitialized = true;

			}
			
			id.init = true;
			stringId.Set (id);
			
		}
		
	}
	
	
	Bytes::Bytes () {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		_root = 0;
		
	}
	
	
	Bytes::Bytes (int size) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		_root = 0;
		
		Resize (size);
		
	}
	
	
	Bytes::Bytes (value bytes) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		_root = 0;
		
		Set (bytes);
		
	}
	
	
	Bytes::Bytes (const char* path) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		_root = 0;
		
		FILE_HANDLE *file = lime::fopen (path, "rb");
		
		if (!file) {
			
			return;
			
		}
		
		lime::fseek (file, 0, SEEK_END);
		int size = lime::ftell (file);
		lime::fseek (file, 0, SEEK_SET);
		
		if (size > 0) {
			
			Resize (size);
			int status = lime::fread (_data, _length, 1, file);
			
		}
		
		lime::fclose (file);
		
	}
	
	
	Bytes::Bytes (const QuickVec<unsigned char> data) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_value = 0;
		_root = 0;
		
		Set (data);
		
	}
	
	
	Bytes::~Bytes () {
		
		if (_root) {
			
			*_root = 0;
			free_root (_root);
			
		}
		
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
	
	
	void Bytes::Resize (int size) {
		
		if (size != _length) {
			
			if (!_value) {
				
				_value = alloc_empty_object ();
				_root = alloc_root ();
				
				if (_root) {
					
					*_root = _value;
					
				}	
				
			}

			BytesId id = stringId.Get ();
			
			if (val_is_null (val_field (_value, id.b))) {
				
				value dataValue;
				
				if (useBuffer) {
					
					buffer b = alloc_buffer_len (size);
					dataValue = buffer_val (b);
					_data = (unsigned char*)buffer_data (b);
					
				} else {
					
					dataValue = alloc_raw_string (size);
					_data = (unsigned char*)val_string (dataValue);
					
				}
				
				alloc_field (_value, id.b, dataValue);
				
			} else {

				int copySize = size < _length ? size : _length;
				
				if (useBuffer) {
					
					buffer b = alloc_buffer_len (size);
					_data = (unsigned char*)buffer_data (b);
					alloc_field (_value, id.b, buffer_val (b));
					
				} else {
					
					value s = alloc_raw_string (size);
					alloc_field (_value, id.b, s);
					_data = (unsigned char*)val_string (s);
					
				}
				
			}
			
			alloc_field (_value, id.length, alloc_int (size));
			
		}
		
		_length = size;
		
	}
	
	
	void Bytes::Set (value bytes) {
		
		if (val_is_null (bytes)) {
			
			_length = 0;
			_data = 0;
			_value = 0;
			
			if (_root) {
				
				*_root = 0;
				free_root (_root);
				
			}
			
			_root = 0;
			
		} else {

			BytesId id = stringId.Get ();
			
			_value = bytes;
			_root = alloc_root ();
			
			if (_root) {
				
				*_root = _value;
				
			}
			
			_length = val_int (val_field (bytes, id.length));
			
			if (_length > 0) {
				
				value b = val_field (bytes, id.b);
				
				if (val_is_string (b)) {
					
					_data = (unsigned char*)val_string (b);
					
				} else {
					
					_data = (unsigned char*)buffer_data (val_to_buffer (b));
					
				}
				
			} else {
				
				_data = 0;
				
			}
			
		}
		
	}
	
	
	void Bytes::Set (const QuickVec<unsigned char> data) {
		
		int size = data.size ();
		
		if (size > 0) {
			
			Resize (size);
			memcpy (_data, &data[0], _length);
			
		} else {
			
			_data = 0;
			_length = 0;
			
			if (_root) {
				
				*_root = 0;
				free_root (_root);
				
			}
			
			_root = 0;
			
		}
		
	}
	
	
	value Bytes::Value () {
		
		if (_value) {
			
			return _value;
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	value lime_bytes_overwrite_file (value inFilename, value inBytes) {
		
		// file is created if it doesn't exist,
		// if it exists, it is truncated to zero
		FILE_HANDLE *file = lime::fopen (val_string (inFilename), "wb");
		
		if (!file) {
			
			#ifdef ANDROID
			// [todo]
			#endif
			return alloc_null();
			
		}
		
		Bytes bytes (inBytes);
		
		// The function fwrite() writes nitems objects, each size bytes long, to the
		// stream pointed to by stream, obtaining them from the location given by
		// ptr.
		// fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
		lime::fwrite (bytes.Data (), 1, bytes.Length (), file);
		
		lime::fclose (file);
		return alloc_null ();
		
	}
	
	
	DEFINE_PRIM (lime_bytes_overwrite_file, 2);
	
	
}