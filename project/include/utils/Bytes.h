#ifndef LIME_UTILS_BYTES_H
#define LIME_UTILS_BYTES_H


#include <hx/CFFI.h>
#include <utils/QuickVec.h>
#include <system/System.h>


namespace lime {
	
	
	struct Bytes {
		
		
		Bytes ();
		Bytes (int size);
		Bytes (value bytes);
		Bytes (const char* path);
		Bytes (const QuickVec<unsigned char> data);
		Bytes (const Bytes &other);
		~Bytes ();
		
		unsigned char *Data ();
		const unsigned char *Data () const;
		int Length () const;
		void Resize (int size);
		void Set (value bytes);
		void Set (const QuickVec<unsigned char> data);
		value Value ();
		int ReadFile (FILE_HANDLE *file);
		void Pin ();
		
		unsigned char *_data;
		int _length;
		AutoGCRoot *_root;
		value _pin;
		
	};
	
	
}


#endif