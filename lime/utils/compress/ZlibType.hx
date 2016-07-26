package lime.utils.compress;

@:cffiCppType("lime::ZlibType")
@:enum abstract ZlibType(Int) from Int to Int from UInt to UInt {
	
	var DEFLATE = 0;
	var GZIP = 1;
	var ZLIB = 2;
	
}