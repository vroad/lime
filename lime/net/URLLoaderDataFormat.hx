package lime.net; #if !flash

#if lime_shared
@:jsRequire("lime", "lime_net_URLLoaderDataFormat") extern
#end
enum URLLoaderDataFormat {
	
	BINARY;
	TEXT;
	VARIABLES;
	
}


#else
typedef URLLoaderDataFormat = flash.net.URLLoaderDataFormat;
#end