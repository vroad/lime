package lime.graphics;

#if lime_shared
@:jsRequire("lime", "lime_graphics_ImageType") extern
#end
enum ImageType {
	
	CANVAS;
	DATA;
	FLASH;
	CUSTOM;
	
}