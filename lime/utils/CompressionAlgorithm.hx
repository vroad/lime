package lime.utils;

#if lime_shared
@:jsRequire("lime", "lime_utils_CompressionAlgorithm") extern
#end
enum CompressionAlgorithm {
	
	DEFLATE;
	ZLIB;
	LZMA;
	GZIP;
	
}