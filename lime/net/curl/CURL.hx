package lime.net.curl;


import lime._internal.utils.CString;
import lime._internal.utils.TimeTPointer;


#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("CURL.xml")
class CURL {
	
	
	public static inline var GLOBAL_SSL:Int = 1 << 0;
	public static inline var GLOBAL_WIN32:Int = 1 << 1;
	public static inline var GLOBAL_ALL:Int = GLOBAL_SSL | GLOBAL_WIN32;
	public static inline var GLOBAL_NOTHING:Int = 0;
	public static inline var GLOBAL_DEFAULT:Int = GLOBAL_ALL;
	public static inline var GLOBAL_ACK_EINTR:Int = 1 << 2;
	
	
	public static function getDate (date:String, now:Float):Float {
		
		#if (lime_native && lime_curl && !macro)
		return curl_getdate (date, now);
		#else
		return 0;
		#end
		
	}
	
	
	public static function globalCleanup ():Void {
		
		#if (lime_native && lime_curl && !macro)
		curl_global_cleanup ();
		#end
		
	}
	
	
	public static function globalInit (flags:Int):CURLCode {
		
		#if (lime_native && lime_curl && !macro)
		return curl_global_init (flags);
		#else
		return 0;
		#end
		
	}
	
	
	public static function version ():String {
		
		#if (lime_native && lime_curl && !macro)
		return curl_version ();
		#else
		return null;
		#end
		
	}
	
	
	public static function versionInfo (type:CURLVersion):Dynamic {
		
		#if (lime_native && lime_curl && !macro)
		return curl_version_info_wrap (type);
		#else
		return null;
		#end
		
	}
	
	
	@:cffi private static function curl_getdate (date:CString, now:TimeTPointer):Float { throw null; }
	@:cffi private static function curl_global_cleanup ():Void { throw null; }
	@:cffi private static function curl_global_init (flags:Int):Int { throw null; }
	@:cffi private static function curl_version ():CString { throw null; }
	@:cffi private static function curl_version_info_wrap (type:Int):Dynamic { throw null; }
	
	
}