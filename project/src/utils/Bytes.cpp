#include <system/System.h>
#include <utils/Bytes.h>
#include <utils/ThreadLocalStorage.h>
#include <hx/CFFIPrimePatch.h>


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
		_root = 0;
		
	}
	
	
	Bytes::Bytes (int size) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_root = 0;
		
		Resize (size);
		
	}
	
	
	Bytes::Bytes (value bytes) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_root = 0;
		
		Set (bytes);
		
	}
	
	
	Bytes::Bytes (const char* path) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_root = 0;
		
		FILE_HANDLE *file = lime::fopen (path, "rb");
		
		ReadFile (file);
		
		lime::fclose (file);
		
	}
	
	
	Bytes::Bytes (const QuickVec<unsigned char> data) {
		
		initialize ();
		
		_data = 0;
		_length = 0;
		_root = 0;
		
		Set (data);
		
	}
	
	
	Bytes::Bytes (const Bytes &other) {
		
		initialize ();
		
		_data = other._data;
		_length = other._length;
		_root = other._root != NULL ? new AutoGCRoot (other._root->get ()) : 0;
		
	}
	
	
	Bytes::~Bytes () {
		
		if (_root) {
			
			delete _root;
			
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
			
			value val;
			
			if (!_root) {
				
				val = alloc_empty_object ();
				
				if (!_root) {
					
					_root = new AutoGCRoot (val);
					
				} else {
					
					_root->set (val);
					
				}
				
			} else {
				
				val = _root->get ();
				
			}

			BytesId id = stringId.Get ();
			
			if (val_is_null (val_field (val, id.b))) {
				
				value dataValue;
				
				if (useBuffer) {
					
					buffer b = alloc_buffer_len (size);
					dataValue = buffer_val (b);
					_data = (unsigned char*)buffer_data (b);
					
				} else {
					
					dataValue = alloc_raw_string (size);
					_data = (unsigned char*)val_string (dataValue);
					
				}
				
				alloc_field (val, id.b, dataValue);
				
			} else {

				int copySize = size < _length ? size : _length;
				
				if (useBuffer) {
					
					buffer b = alloc_buffer_len (size);
					_data = (unsigned char*)buffer_data (b);
					alloc_field (val, id.b, buffer_val (b));
					
				} else {
					
					value s = alloc_raw_string (size);
					alloc_field (val, id.b, s);
					_data = (unsigned char*)val_string (s);
					
				}
				
			}
			
			alloc_field (val, id.length, alloc_int (size));
			
		}
		
		_length = size;
		
	}
	
	
	void Bytes::Set (value bytes) {
		
		if (val_is_null (bytes)) {
			
			_length = 0;
			_data = 0;
			
			if (_root) {
				
				delete _root;
				
			}
			
			_root = 0;
			
		} else {
			
			BytesId id = stringId.Get ();
			
			if (_root == NULL) {
				
				_root = new AutoGCRoot (bytes);
				
			} else {
				
				_root->set (bytes);
				
			}
			
			_length = val_int (val_field (bytes, id.length));
			
			if (_length > 0) {
				
				value b = val_field (bytes, id.b);
				
				if (val_is_string (b)) {
					
					_data = (unsigned char*)val_string (b);
					
				} else if (!val_is_null (b)) {
					
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
				
				delete _root;
				
			}
			
			_root = 0;
			
		}
		
	}
	
	
	value Bytes::Value () {
		
		if (_root) {
			
			return _root->get ();
			
		} else {
			
			return alloc_null ();
			
		}
		
	}
	
	
	int Bytes::ReadFile (FILE_HANDLE *file) {
		
		if (!file) {
			
			return 0;
			
		}
		
		lime::fseek (file, 0, SEEK_END);
		int size = lime::ftell (file);
		lime::fseek (file, 0, SEEK_SET);
		
		Resize (size);
		
		if (size > 0) {
			
			return lime::fread (_data, _length, 1, file);
			
		}
		
		return 0;
		
	}
	
	
	void lime_bytes_overwrite_file (HxString inFilename, value inBytes) {
		
		// file is created if it doesn't exist,
		// if it exists, it is truncated to zero
		FILE_HANDLE *file = lime::fopen (inFilename.__s, "wb");
		
		if (!file) {
			
			#ifdef ANDROID
			// [todo]
			#endif
			
		}
		
		Bytes bytes (inBytes);
		
		// The function fwrite() writes nitems objects, each size bytes long, to the
		// stream pointed to by stream, obtaining them from the location given by
		// ptr.
		// fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
		lime::fwrite (bytes.Data (), 1, bytes.Length (), file);
		
		lime::fclose (file);
		
	}
	
	
	DEFINE_PRIME2v (lime_bytes_overwrite_file);
	
	
}