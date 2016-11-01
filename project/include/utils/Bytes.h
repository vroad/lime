#ifndef LIME_UTILS_BYTES_H
#define LIME_UTILS_BYTES_H


#include <hx/CFFI.h>
#include <utils/QuickVec.h>
#include <system/System.h>


namespace lime {
	
	
	class Bytes {
		
		
	public:
		
		
		Bytes ();
		Bytes (int size);
		Bytes (value bytes);
		Bytes (const char* path);
		Bytes (const QuickVec<unsigned char> data);
		~Bytes ();
		
		void Clear ();
		unsigned char *Data ();
		const unsigned char *Data () const;
		int Length () const;
		value Pin ();
		int ReadFile (const char* path);
		int ReadFile (FILE_HANDLE *file);
		void Resize (int size);
		bool Set (value bytes);
		void Set (const QuickVec<unsigned char> data);
		static void Unpin (value pin);
		value Value ();
		
		unsigned char *_data;
		int _length;
		value _value;
		
		
	};
	
	
}


#endif