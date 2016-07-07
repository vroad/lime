package lime.utils;

@:cffiCppType("lime::ArrayBufferView*")
typedef AnonArrayBufferView = {
	
	buffer:Dynamic,
	byteLength:Int,
	byteOffset:Int
	
}