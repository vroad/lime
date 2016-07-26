#ifndef LIME_UTILS_COMPRESS_ZLIB_H
#define LIME_UTILS_COMPRESS_ZLIB_H


#include <utils/Bytes.h>


namespace lime {
	
	
	enum ZlibType {
		
		DEFLATE,
		GZIP,
		ZLIB
		
	};
	
	
	class Zlib {
		
		
		public:
			
			static value Compress (ZlibType type, Bytes* data);
			static value Decompress (ZlibType type, Bytes* data);
		
		
	};
	
	
}


#endif