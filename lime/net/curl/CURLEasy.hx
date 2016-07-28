package lime.net.curl;


import haxe.io.Bytes;
import lime._internal.net.curl.CURLEasyHandle;
import lime._internal.utils.CString;
import lime._internal.utils.SizeTPointer;
import lime.net.curl.CURL;
using lime.utils.BytesTools;

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("CURLEasy.xml")
class CURLEasy {
	
	@:cffiHandle public var handle(default, null):CURLEasyHandle;
	
	private function new (handle:CURLEasyHandle) {
		
		this.handle = handle;
		
	}
	
	public function cleanup ():Void {
		
		#if (lime_native && lime_curl && !macro)
		curl_easy_cleanup (handle);
		#end
		
	}
	
	
	public function duphandle ():CURLEasy {
		
		#if (lime_native && lime_curl && !macro)
		var handle = curl_easy_duphandle (handle);
		return new CURLEasy (handle);
		#else
		return null;
		#end
		
	}
	
	
	public function escape (url:String, length:Int):String {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_escape (handle, url, length);
		#else
		return null;
		#end
		
	}
	
	
	public function getinfo (info:CURLInfo):Dynamic {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_getinfo_wrap (handle, info);
		#else
		return null;
		#end
		
	}
	
	
	public static function create ():CURLEasy {
		
		#if (lime_native && lime_curl && !macro)
		var handle = curl_easy_init ();
		return new CURLEasy (handle);
		#else
		return null;
		#end
		
	}
	
	
	public function pause (bitMask:Int):CURLCode {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_pause (handle, bitMask);
		#else
		return 0;
		#end
		
	}
	
	
	public function perform ():CURLCode {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_perform (handle);
		#else
		return 0;
		#end
		
	}
	
	
	/*public static function recv (handle:Dynamic):CURLCode {
		
		#if ((cpp || neko || nodejs) && lime_curl && !macro)
		return cast lime_curl_easy_perform (handle);
		#else
		return cast 0;
		#end
		
	}*/
	
	
	public function reset ():Void {
		
		#if (lime_native && lime_curl && !macro)
		curl_easy_reset (handle);
		#end
		
	}
	
	
	/*public static function send (handle:Dynamic):CURLCode {
		
		#if ((cpp || neko || nodejs) && lime_curl && !macro)
		return cast lime_curl_easy_perform (handle);
		#else
		return cast 0;
		#end
		
	}*/
	
	
	public function setopt (option:CURLOption, parameter:Dynamic):CURLCode {
		
		#if (lime_native && lime_curl && !macro)
		if (option == CURLOption.WRITEFUNCTION || option == CURLOption.HEADERFUNCTION) {
			
			parameter = __writeCallback.bind (parameter);
			
		}
		return curl_easy_setopt (handle, cast (option, Int), parameter);
		#else
		return 0;
		#end
		
	}
	
	
	public function strerror (code:CURLCode):String {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_strerror (cast (code, Int));
		#else
		return null;
		#end
		
	}
	
	
	public function unescape (url:String):String {
		
		#if (lime_native && lime_curl && !macro)
		return curl_easy_unescape_wrap (handle, url);
		#else
		return null;
		#end
		
	}
	
	
	private function __writeCallback (callback:Dynamic, output:Dynamic, size:Int, nmemb:Int):Int {
		
		#if (lime_native && lime_curl && !macro)
		var bytes:Bytes = null;
		
		if (output != null) {
			
			bytes = Bytes.ofLengthAndData (output.length, output.b);
			
		}
		
		return callback (bytes, size, nmemb);
		
		#else
		
		return 0;
		
		#end
		
	}
	
	
	#if (lime_native && lime_curl && !macro)
	@:cffi private static function curl_easy_cleanup (handle:CURLEasyHandle):Void;
	@:cffi private static function curl_easy_duphandle (handle:CURLEasyHandle):CURLEasyHandle;
	@:cffi private static function curl_easy_escape (curl:CURLEasyHandle, url:CString, length:Int):CString;
	@:cffi private static function curl_easy_getinfo_wrap (curl:CURLEasyHandle, info:Int):Dynamic;
	@:cffi private static function curl_easy_init ():CURLEasyHandle;
	@:cffi private static function curl_easy_pause (handle:CURLEasyHandle, bitmask:Int):Int;
	@:cffi private static function curl_easy_perform (easy_handle:CURLEasyHandle):Int;
	@:cffi private static function curl_easy_recv (curl:CURLEasyHandle, buffer:Dynamic, buflen:Int, n:SizeTPointer):Int;
	@:cffi private static function curl_easy_reset (curl:CURLEasyHandle):Void;
	@:cffi private static function curl_easy_send (curl:CURLEasyHandle, buffer:Dynamic, buflen:Int, n:SizeTPointer):Int;
	@:cffi private static function curl_easy_setopt (handle:CURLEasyHandle, option:CURLOption, parameter:Dynamic):Int;
	@:cffi private static function curl_easy_strerror (errornum:CURLCode):CString;
	@:cffi private static function curl_easy_unescape_wrap (curl:CURLEasyHandle, url:CString):Dynamic;
	#end
	
	
}