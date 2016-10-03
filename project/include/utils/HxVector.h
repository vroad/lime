#ifndef LIME_UTILS_HX_VECTOR_H
#define LIME_UTILS_HX_VECTOR_H

#include <hx/CFFI.h>
#include <system/CFFIPointer.h>
#include "PointerUtils.h"

namespace lime {
	
	template <typename T>
	class HxVector {
		
	public:
		
		HxVector () {
			
			Reset ();
			
		}
		
		HxVector (T* data, size_t length, bool ownsPoiner) {
			
			Set (data, length, ownsPoiner);
			
		}
		
		~HxVector () {
			
			if (ownsPoiner) {
				
				delete data;
				
			}
			
		}
		
		void Reset () {
			
			this->data = NULL;
			this->length = 0;
			this->ownsPoiner = false;
			
		}
		
		void Set (T* data, size_t length, bool ownsPoiner) {
			
			this->data = data;
			this->length = length;
			this->ownsPoiner = ownsPoiner;
			
		}
		
		T* Data () const {
			
			return data;
			
		}
		
		size_t Length () const {
			
			return length;
			
		}
		
	private:
		
		HxVector (const HxVector<T>& other) {}
		
		T* data;
		size_t length;
		bool ownsPoiner;
		
	};
	
	static void val_to_hx_vector_double (value inArray, HxVector<double>& outVector) {
		
		int length = val_array_size (inArray);
		
		if (length <= 0) {
			
			outVector.Reset ();
			return;
			
		}
		
		double* result = val_array_double (inArray);
		
		if (result) {
			
			outVector.Set (result, length, false);
			return;
			
		}
		
		result = new double (length);
		
		for (int i = 0; i < length; i++) {
			
			result[i] = val_number (val_array_i (inArray, i));
			
		}
		
		outVector.Set (result, length, true);
		
	}
	
	static void val_to_hx_vector_float (value inArray, HxVector<float>& outVector) {
		
		int length = val_array_size (inArray);
		
		if (length <= 0) {
			
			outVector.Reset ();
			return;
			
		}
		
		float* result = val_array_float (inArray);
		
		if (result) {
			
			outVector.Set (result, length, false);
			return;
			
		}
		
		result = new float (length);
		
		for (int i = 0; i < length; i++) {
			
			result[i] = val_float (val_array_i (inArray, i));
			
		}
		
		outVector.Set (result, length, true);
		
	}
	
	static void val_to_hx_vector_int (value inArray, HxVector<int>& outVector) {
		
		int length = !val_is_null (inArray) ? val_array_size (inArray) : 0;
		
		if (length <= 0) {
			
			outVector.Reset ();
			return;
			
		}
		
		int* result = val_array_int (inArray);
		
		if (result) {
			
			outVector.Set (result, length, false);
			return;
			
		}
		
		result = new int (length);
		
		for (int i = 0; i < length; i++) {
			
			result[i] = val_int (val_array_i (inArray, i));
			
		}
		
		outVector.Set (result, length, true);
		
	}
	
}

#endif