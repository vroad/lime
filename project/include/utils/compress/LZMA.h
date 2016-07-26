#ifndef LIME_UTILS_COMPRESS_LZMA_H
#define LIME_UTILS_COMPRESS_LZMA_H


#include <utils/Bytes.h>


namespace lime {
	
	
	class LZMA {
		
		
		public:
			
			static value Compress (Bytes* data);
			static value Decompress (Bytes* data);
		
		
	};
	
	
}


#endif