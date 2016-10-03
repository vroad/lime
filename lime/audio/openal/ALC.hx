package lime.audio.openal;

import lime._internal.audio.openal.ALCContextWrapperHandle;
import lime._internal.audio.openal.ALCContextWrapperNullableHandle;
import lime._internal.audio.openal.ALCDeviceHandle;
import lime._internal.utils.CString;
import lime._internal.utils.HxVector_Int;
import lime.system.CFFIPointer;

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("ALC.xml")
class ALC {
	
	
	public static inline var FALSE:Int = 0;
	public static inline var TRUE:Int = 1;
	public static inline var FREQUENCY:Int = 0x1007;
	public static inline var REFRESH:Int = 0x1008;
	public static inline var SYNC:Int = 0x1009;
	public static inline var MONO_SOURCES:Int = 0x1010;
	public static inline var STEREO_SOURCES:Int = 0x1011;
	public static inline var NO_ERROR:Int = 0;
	public static inline var INVALID_DEVICE:Int = 0xA001;
	public static inline var INVALID_CONTEXT:Int = 0xA002;
	public static inline var INVALID_ENUM:Int = 0xA003;
	public static inline var INVALID_VALUE:Int = 0xA004;
	public static inline var OUT_OF_MEMORY:Int = 0xA005;
	public static inline var ATTRIBUTES_SIZE:Int = 0x1002;
	public static inline var ALL_ATTRIBUTES:Int = 0x1003;
	public static inline var DEFAULT_DEVICE_SPECIFIER:Int = 0x1004;
	public static inline var DEVICE_SPECIFIER:Int = 0x1005;
	public static inline var EXTENSIONS:Int = 0x1006;
	public static inline var ENUMERATE_ALL_EXT:Int = 1;
	public static inline var DEFAULT_ALL_DEVICES_SPECIFIER:Int = 0x1012;
	public static inline var ALL_DEVICES_SPECIFIER:Int = 0x1013;
	
	private static var currentContext:ALContext = null;
	
	public static function closeDevice (device:ALDevice):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alcCloseDevice_wrap (device);
		#else
		return false;
		#end
		
	}
	
	
	public static function createContext (device:ALDevice, attrlist:Array<Int> = null):ALContext {
		
		#if (lime_cffi && lime_openal && !macro)
		var handle:Dynamic = alcCreateContext_wrap (device, attrlist);
		
		if (handle != null) {
			
			return new ALContext (handle);
			
		}
		#end
		
		return null;
		
	}
	
	
	public static function destroyContext (context:ALContext):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alcDestroyContext_wrap (context);
		#end
		
	}
	
	
	public static function getContextsDevice (context:ALContext):ALDevice {
		
		#if (lime_cffi && lime_openal && !macro)
		var handle:CFFIPointer = alcGetContextsDevice_wrap (context);
		
		if (handle != null) {
			
			return new ALDevice (handle);
			
		}
		#end
		
		return null;
		
	}
	
	
	public static function getCurrentContext ():ALContext {
		
		return currentContext;
		
	}
	
	
	public static function getError (device:ALDevice):Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alcGetError (device);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getErrorString (device:ALDevice):String {
		
		return switch (getError (device)) {
			
			case INVALID_DEVICE: "INVALID_DEVICE: Invalid device (or no device?)";
			case INVALID_CONTEXT: "INVALID_CONTEXT: Invalid context (or no context?)";
			case INVALID_ENUM: "INVALID_ENUM: Invalid enum value";
			case INVALID_VALUE: "INVALID_VALUE: Invalid param value";
			case OUT_OF_MEMORY: "OUT_OF_MEMORY: OpenAL has run out of memory";
			default: "";
			
		}
		
	}
	
	
	public static function getIntegerv (device:ALDevice, param:Int, size:Int):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alcGetIntegerv_wrap (device, param, size);
		#else
		return null;
		#end
		
	}
	
	
	public static function getString (device:ALDevice, param:Int):String {
		
		#if (lime_cffi && lime_openal && !macro)
		return alcGetString (device, param);
		#else
		return null;
		#end
		
	}
	
	
	public static function makeContextCurrent (context:ALContext):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		currentContext = context;
		return alcMakeContextCurrent_wrap (context);
		#else
		return false;
		#end
		
	}
	
	
	public static function openDevice (deviceName:String = null):ALDevice {
		
		#if (lime_cffi && lime_openal && !macro)
		var handle = alcOpenDevice (deviceName);
		
		if (handle != null) {
			
			return new ALDevice (handle);
			
		}
		#end
		
		return null;
		
	}
	
	
	public static function pauseDevice (device:ALDevice):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alcDevicePauseSOFT (device);
		#end
		
	}
	
	
	public static function processContext (context:ALContext):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alcProcessContext_wrap (context);
		#end
		
	}
	
	
	public static function resumeDevice (device:ALDevice):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alcDeviceResumeSOFT (device);
		#end
		
	}
	
	
	public static function suspendContext (context:ALContext):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alcSuspendContext_wrap (context);
		#end
		
	}
	
	
	#if (lime_cffi && lime_openal && !macro)
	@:cffi private static function alcCloseDevice_wrap (device:CFFIPointer):Bool;
	@:cffi private static function alcCreateContext_wrap (device:CFFIPointer, attrlist:HxVector_Int):ALCContextWrapperHandle;
	@:cffi private static function alcDestroyContext_wrap (context:CFFIPointer):Void;
	@:cffi private static function alcGetContextsDevice_wrap (context:ALCContextWrapperHandle):CFFIPointer;
	@:cffi private static function alcGetError (device:ALCDeviceHandle):Int;
	@:cffi private static function alcGetIntegerv_wrap (device:ALCDeviceHandle, param:Int, size:Int):Dynamic;
	@:cffi private static function alcGetString (device:ALCDeviceHandle, param:Int):String;
	@:cffi private static function alcMakeContextCurrent_wrap (context:ALCContextWrapperNullableHandle):Bool;
	@:cffi private static function alcOpenDevice (devicename:CString):ALCDeviceHandle;
	@:cffi private static function alcProcessContext_wrap (context:ALCContextWrapperHandle):Void;
	@:cffi private static function alcSuspendContext_wrap (context:ALCContextWrapperHandle):Void;
	@:cffi private static function alcDevicePauseSOFT (device:ALCDeviceHandle):Void;
	@:cffi private static function alcDeviceResumeSOFT (device:ALCDeviceHandle):Void;
	#end
	
	
}