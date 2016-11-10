package lime.audio.openal;


import lime.system.CFFIPointer;
import lime._internal.audio.openal.ALCContextWrapperHandle;
import lime._internal.audio.openal.ALBufferHandle;
import lime._internal.audio.openal.ALSourceHandle;
import lime._internal.utils.HxVector_Float;
import lime._internal.utils.HxVector_Int;
import lime._internal.utils.CString;
import lime._internal.utils.LimeArrayBufferView;
import lime.utils.AnonBytesUtils;
import lime.utils.ArrayBufferView;
using lime.utils.ArrayBufferViewTools;
using Lambda;

#if cpp
import cpp.Float32;
#else
@:cffiCppType("float", "cpp.Float32")
typedef Float32 = Float;
#end

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("AL.xml")
class AL {
	
	
	public static inline var NONE:Int = 0;
	public static inline var FALSE:Int = 0;
	public static inline var TRUE:Int = 1;
	public static inline var SOURCE_RELATIVE:Int = 0x202;
	public static inline var CONE_INNER_ANGLE:Int = 0x1001;
	public static inline var CONE_OUTER_ANGLE:Int = 0x1002;
	public static inline var PITCH:Int = 0x1003;
	public static inline var POSITION:Int = 0x1004;
	public static inline var DIRECTION:Int = 0x1005;
	public static inline var VELOCITY:Int = 0x1006;
	public static inline var LOOPING:Int = 0x1007;
	public static inline var BUFFER:Int = 0x1009;
	public static inline var GAIN:Int = 0x100A;
	public static inline var MIN_GAIN:Int = 0x100D;
	public static inline var MAX_GAIN:Int = 0x100E;
	public static inline var ORIENTATION:Int = 0x100F;
	public static inline var SOURCE_STATE:Int = 0x1010;
	public static inline var INITIAL:Int = 0x1011;
	public static inline var PLAYING:Int = 0x1012;
	public static inline var PAUSED:Int = 0x1013;
	public static inline var STOPPED:Int = 0x1014;
	public static inline var BUFFERS_QUEUED:Int = 0x1015;
	public static inline var BUFFERS_PROCESSED:Int = 0x1016;
	public static inline var REFERENCE_DISTANCE:Int = 0x1020;
	public static inline var ROLLOFF_FACTOR:Int = 0x1021;
	public static inline var CONE_OUTER_GAIN:Int = 0x1022;
	public static inline var MAX_DISTANCE:Int = 0x1023;
	public static inline var SEC_OFFSET:Int = 0x1024;
	public static inline var SAMPLE_OFFSET:Int = 0x1025;
	public static inline var BYTE_OFFSET:Int = 0x1026;
	public static inline var SOURCE_TYPE:Int = 0x1027;
	public static inline var STATIC:Int = 0x1028;
	public static inline var STREAMING:Int = 0x1029;
	public static inline var UNDETERMINED:Int = 0x1030;
	public static inline var FORMAT_MONO8:Int = 0x1100;
	public static inline var FORMAT_MONO16:Int = 0x1101;
	public static inline var FORMAT_STEREO8:Int = 0x1102;
	public static inline var FORMAT_STEREO16:Int = 0x1103;
	public static inline var FREQUENCY:Int = 0x2001;
	public static inline var BITS:Int = 0x2002;
	public static inline var CHANNELS:Int = 0x2003;
	public static inline var SIZE:Int = 0x2004;
	public static inline var NO_ERROR:Int = 0;
	public static inline var INVALID_NAME:Int = 0xA001;
	public static inline var INVALID_ENUM:Int = 0xA002;
	public static inline var INVALID_VALUE:Int = 0xA003;
	public static inline var INVALID_OPERATION:Int = 0xA004;
	public static inline var OUT_OF_MEMORY:Int = 0xA005;
	public static inline var VENDOR:Int = 0xB001;
	public static inline var VERSION:Int = 0xB002;
	public static inline var RENDERER:Int = 0xB003;
	public static inline var EXTENSIONS:Int = 0xB004;
	public static inline var DOPPLER_FACTOR:Int = 0xC000;
	public static inline var SPEED_OF_SOUND:Int = 0xC003;
	public static inline var DOPPLER_VELOCITY:Int = 0xC001;
	public static inline var DISTANCE_MODEL:Int = 0xD000;
	public static inline var INVERSE_DISTANCE:Int = 0xD001;
	public static inline var INVERSE_DISTANCE_CLAMPED:Int = 0xD002;
	public static inline var LINEAR_DISTANCE:Int = 0xD003;
	public static inline var LINEAR_DISTANCE_CLAMPED:Int = 0xD004;
	public static inline var EXPONENT_DISTANCE:Int = 0xD005;
	public static inline var EXPONENT_DISTANCE_CLAMPED:Int = 0xD006;
	
	
	public static function bufferData (buffer:ALBuffer, format:Int, data:ArrayBufferView, size:Int, freq:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBufferData_wrap (buffer != null ? buffer.handle : null, format, data.toAnonArrayBufferView (), size, freq);
		#end
		
	}
	
	
	public static function buffer3f (buffer:ALBuffer, param:Int, value1:Float, value2:Float, value3:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBuffer3f_wrap (buffer != null ? buffer.handle : null, param, value1, value2, value3);
		#end
		
	}
	
	
	public static function buffer3i (buffer:ALBuffer, param:Int, value1:Int, value2:Int, value3:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBuffer3i_wrap (buffer != null ? buffer.handle : null, param, value1, value2, value3);
		#end
		
	}
	
	
	public static function bufferf (buffer:ALBuffer, param:Int, value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBufferf_wrap (buffer != null ? buffer.handle : null, param, value);
		#end
		
	}
	
	
	public static function bufferfv (buffer:ALBuffer, param:Int, values:Array<Float>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBufferfv_wrap (buffer != null ? buffer.handle : null, param, values);
		#end
		
	}
	
	
	public static function bufferi (buffer:ALBuffer, param:Int, value:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBufferi_wrap (buffer != null ? buffer.handle : null, param, value);
		#end
		
	}
	
	
	public static function bufferiv (buffer:ALBuffer, param:Int, values:Array<Int>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alBufferiv_wrap (buffer != null ? buffer.handle : null, param, values);
		#end
		
	}
	
	
	public static function deleteBuffer (buffer:ALBuffer):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDeleteBuffer_wrap (buffer != null ? buffer.handle : null);
		#end
		
	}
	
	
	public static function deleteBuffers (buffers:Array<ALBuffer>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDeleteBuffers_wrap (__getHandlesFromBuffers (buffers));
		#end
		
	}
	
	
	public static function deleteSource (source:ALSource):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDeleteSource_wrap (source != null ? source.handle : null);
		#end
		
	}
	
	
	public static function deleteSources (sources:Array<ALSource>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		var handles = __getHandlesFromSources (sources);
		alDeleteSources_wrap (handles);
		#end
		
	}
	
	
	public static function disable (capability:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDisable (capability);
		#end
		
	}
	
	
	public static function distanceModel (distanceModel:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDistanceModel (distanceModel);
		#end
		
	}
	
	
	public static function dopplerFactor (value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDopplerFactor (value);
		#end
		
	}
	
	
	public static function dopplerVelocity (value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alDopplerVelocity (value);
		#end
		
	}
	
	
	public static function enable (capability:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alEnable (capability);
		#end
		
	}
	
	
	public static function genSource ():ALSource {
		
		#if (lime_cffi && lime_openal && !macro)
		var ctx = ALC.getCurrentContext ();
		
		if (ctx == null) {
			
			return null;
			
		}
		
		var handle = alGenSource_wrap (ctx.handle);
		return handle != null ? new ALSource (handle) : null;
		#else
		return null;
		#end
		
	}
	
	
	public static function genSources (n:Int):Array<ALSource> {
		
		#if (lime_cffi && lime_openal && !macro)
		var ctx = ALC.getCurrentContext ();
		
		if (ctx == null) {
			
			return null;
			
		}
		
		var handles = alGenSources_wrap (ctx.handle, n);
		
		return handles != null ? handles.map (function (handle:ALSourceHandle) {
			
			return new ALSource (handle);
			
		}) : null;
		#else
		return null;
		#end
		
	}
	
	
	public static function genBuffer ():ALBuffer {
		
		#if (lime_cffi && lime_openal && !macro)
		var ctx = ALC.getCurrentContext ();
		
		if (ctx == null) {
			
			return null;
			
		}
		
		var handle = alGenBuffer_wrap (ctx.handle);
		return handle != null ? new ALBuffer (handle) : null;
		#else
		return null;
		#end
		
	}
	
	
	public static function genBuffers (n:Int):Array<ALBuffer> {
		
		#if (lime_cffi && lime_openal && !macro)
		var ctx = ALC.getCurrentContext ();
		
		if (ctx == null) {
			
			return null;
			
		}
		
		var handles = alGenBuffers_wrap (ctx.handle, n);
		return handles != null ? handles.map (function (handle:ALBufferHandle) {
			
			return new ALBuffer (handle);
			
		}) : null;
		#else
		return null;
		#end
		
	}
	
	
	public static function getBoolean (param:Int):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBoolean (param);
		#else
		return false;
		#end
		
	}
	
	
	public static function getBooleanv (param:Int, count:Int = 1):Array<Bool> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBooleanv_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getBuffer3f (buffer:ALBuffer, param:Int):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBuffer3f_wrap (buffer != null ? buffer.handle : null, param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getBuffer3i (buffer:ALBuffer, param:Int):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBuffer3i_wrap (buffer != null ? buffer.handle : null, param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getBufferf (buffer:ALBuffer, param:Int):Float {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBufferf_wrap (buffer != null ? buffer.handle : null, param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getBufferfv (buffer:ALBuffer, param:Int, count:Int = 1):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBufferfv_wrap (buffer != null ? buffer.handle : null, param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getBufferi (buffer:ALBuffer, param:Int):Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBufferi_wrap (buffer != null ? buffer.handle : null, param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getBufferiv (buffer:ALBuffer, param:Int, count:Int = 1):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetBufferiv_wrap (buffer != null ? buffer.handle : null, param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getDouble (param:Int):Float {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetDouble (param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getDoublev (param:Int, count:Int = 1):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetDoublev_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getEnumValue (ename:String):Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetEnumValue (ename);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getError ():Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetError ();
		#else
		return 0;
		#end
		
	}
	
	
	public static function getErrorString ():String {
		
		return switch (getError ()) {
			
			case INVALID_NAME: "INVALID_NAME: Invalid parameter name";
			case INVALID_ENUM: "INVALID_ENUM: Invalid enum value";
			case INVALID_VALUE: "INVALID_VALUE: Invalid parameter value";
			case INVALID_OPERATION: "INVALID_OPERATION: Illegal operation or call";
			case OUT_OF_MEMORY: "OUT_OF_MEMORY: OpenAL has run out of memory";
			default: "";
			
		}
		
	}
	
	
	public static function getFloat (param:Int):Float {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetFloat (param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getFloatv (param:Int, count:Int = 1):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetFloatv_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getInteger (param:Int):Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetInteger (param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getIntegerv (param:Int, count:Int = 1):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetIntegerv_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getListener3f (param:Int):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListener3f_wrap (param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getListener3i (param:Int):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListener3i_wrap (param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getListenerf (param:Int):Float {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListenerf_wrap (param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getListenerfv (param:Int, count:Int = 1):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListenerfv_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getListeneri (param:Int):Int {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListeneri_wrap (param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getListeneriv (param:Int, count:Int = 1):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetListeneriv_wrap (param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getSource3f (source:ALSource, param:Int):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSource3f_wrap (source != null ? source.handle : null, param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getSourcef (source:ALSource, param:Int):Float {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSourcef_wrap (source != null ? source.handle : null, param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getSource3i (source:ALSource, param:Int):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSource3i_wrap (source != null ? source.handle : null, param);
		#else
		return null;
		#end
		
	}
	
	
	public static function getSourcefv (source:ALSource, param:Int, count:Int = 1):Array<Float> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSourcefv_wrap (source != null ? source.handle : null, param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getSourcei (source:ALSource, param:Int):Dynamic {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSourcei_wrap (source != null ? source.handle : null, param);
		#else
		return 0;
		#end
		
	}
	
	
	public static function getSourceiv (source:ALSource, param:Int, count:Int = 1):Array<Int> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetSourceiv_wrap (source != null ? source.handle : null, param, count);
		#else
		return null;
		#end
		
	}
	
	
	public static function getString (param:Int):String {
		
		#if (lime_cffi && lime_openal && !macro)
		return alGetString (param);
		#else
		return null;
		#end
		
	}
	
	
	public static function isBuffer (buffer:ALBuffer):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alIsBuffer_wrap (buffer != null ? buffer.handle : null);
		#else
		return false;
		#end
		
	}	
	
	
	public static function isEnabled (capability:Int):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alIsEnabled (capability);
		#else
		return false;
		#end
		
	}
	
	
	public static function isExtensionPresent (extname:String):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alIsExtensionPresent (extname);
		#else
		return false;
		#end
		
	}
	
	
	public static function isSource (source:ALSource):Bool {
		
		#if (lime_cffi && lime_openal && !macro)
		return alIsSource_wrap (source != null ? source.handle : null);
		#else
		return false;
		#end
		
	}
	
	
	public static function listener3f (param:Int, value1:Float, value2:Float, value3:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListener3f (param, value1, value2, value3);
		#end
		
	}
	
	
	public static function listener3i (param:Int, value1:Int, value2:Int, value3:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListener3i (param, value1, value2, value3);
		#end
		
	}
	
	
	public static function listenerf (param:Int, value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListenerf (param, value);
		#end
		
	}
	
	
	public static function listenerfv (param:Int, values:Array<Float>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListenerfv_wrap (param, values);
		#end
		
	}
	
	
	public static function listeneri (param:Int, value:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListeneri (param, value);
		#end
		
	}
	
	
	public static function listeneriv (param:Int, values:Array<Int>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alListeneriv_wrap (param, values);
		#end
		
	}
	
	
	public static function source3f (source:ALSource, param:Int, value1:Float, value2:Float, value3:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSource3f_wrap (source != null ? source.handle : null, param, value1, value2, value3);
		#end
		
	}
	
	
	public static function source3i (source:ALSource, param:Int, value1:Int, value2:Int, value3:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSource3i_wrap (source != null ? source.handle : null, param, value1, value2, value3);
		#end
		
	}
	
	
	public static function sourcef (source:ALSource, param:Int, value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcef_wrap (source != null ? source.handle : null, param, value);
		#end
		
	}
	
	
	public static function sourcefv (source:ALSource, param:Int, values:Array<Float>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcefv_wrap (source != null ? source.handle : null, param, values);
		#end
		
	}
	
	
	public static function sourcei (source:ALSource, param:Int, value:Int):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcei_wrap (source != null ? source.handle : null, param, value);
		#end
		
	}
	
	
	public static function sourceiv (source:ALSource, param:Int, values:Array<Int>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceiv_wrap (source != null ? source.handle : null, param, values);
		#end
		
	}
	
	
	public static function sourceBuffer (source:ALSource, buffer:ALBuffer):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceBuffer (source != null ? source.handle : null, buffer.handle);
		#end
		
	}
	
	
	public static function sourcePlay (source:ALSource):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcePlay_wrap (source != null ? source.handle : null);
		#end
		
	}
	
	
	public static function sourcePlayv (sources:Array<ALSource>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		var handles = sources != null ? sources.map (function (src:ALSource) {
			
			return src.handle;
			
		}) : null;
		alSourcePlayv_wrap (handles);
		#end
		
	}
	
	
	public static function sourceStop (source:ALSource):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceStop_wrap (source != null ? source.handle : null);
		#end
		
	}
	
	
	public static function sourceStopv (sources:Array<ALSource>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceStopv_wrap (__getHandlesFromSources (sources));
		#end
		
	}
	
	
	public static function sourceRewind (source:ALSource):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceRewind_wrap (source != null ? source.handle : null);
		#end
		
	}
	
	
	public static function sourceRewindv (sources:Array<ALSource>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceRewindv_wrap (__getHandlesFromSources (sources));
		#end
		
	}
	
	
	public static function sourcePause (source:ALSource):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcePause_wrap (source != null ? source.handle : null);
		#end
		
	}
	
	
	public static function sourcePausev (sources:Array<ALSource>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourcePausev_wrap (__getHandlesFromSources (sources));
		#end
		
	}
	
	
	public static function sourceQueueBuffer (source:ALSource, buffer:ALBuffer):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		var buffers:Array<ALBufferHandle> = buffer != null ? [ buffer.handle ] : null;
		alSourceQueueBuffers_wrap (source != null ? source.handle : null, 1, buffers);
		#end
		
	}
	
	
	public static function sourceQueueBuffers (source:ALSource, nb:Int, buffers:Array<ALBuffer>):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSourceQueueBuffers_wrap (source != null ? source.handle : null, nb, __getHandlesFromBuffers (buffers));
		#end
		
	}
	
	
	public static function sourceUnqueueBuffer (source:ALSource):ALBuffer {
		
		#if (lime_cffi && lime_openal && !macro)
		var res = alSourceUnqueueBuffers_wrap (source != null ? source.handle : null, 1);
		return res[0];
		#else
		return null;
		#end
		
	}
	
	
	public static function sourceUnqueueBuffers (source:ALSource, nb:Int):Array<ALBuffer> {
		
		#if (lime_cffi && lime_openal && !macro)
		return alSourceUnqueueBuffers_wrap (source != null ? source.handle : null, nb);
		#else
		return null;
		#end
		
	}
	
	
	public static function speedOfSound (value:Float):Void {
		
		#if (lime_cffi && lime_openal && !macro)
		alSpeedOfSound (value);
		#end
		
	}
	
	
	private static function __getHandlesFromBuffers (buffers:Array<ALBuffer>):Array<ALBufferHandle> {
		
		return buffers != null ? buffers.map (function (buf:ALBuffer) {
			
			return buf.handle;
			
		}) : null;
		
	}
	
	
	private static function __getHandlesFromSources (sources:Array<ALSource>):Array<ALSourceHandle> {
		
		return sources != null ? sources.map (function (src:ALSource) {
			
			return src.handle;
			
		}) : null;
		
	}
	
	
	#if (lime_cffi && lime_openal && !macro)
	@:cffi private static function alBufferData_wrap (buffer:ALBufferHandle, format:Int, data:LimeArrayBufferView, size:Int, freq:Int):Void;
	@:cffi private static function alBuffer3f_wrap (buffer:ALBufferHandle, param:Int, value1:Float32, value2:Float32, value3:Float32):Void;
	@:cffi private static function alBuffer3i_wrap (buffer:ALBufferHandle, param:Int, value1:Int, value2:Int, value3:Int):Void;
	@:cffi private static function alBufferf_wrap (buffer:ALBufferHandle, param:Int, value:Float32):Void;
	@:cffi private static function alBufferfv_wrap (buffer:ALBufferHandle, param:Int, values:HxVector_Float):Void;
	@:cffi private static function alBufferi_wrap (buffer:ALBufferHandle, param:Int, value:Int):Void;
	@:cffi private static function alBufferiv_wrap (buffer:ALBufferHandle, param:Int, values:HxVector_Int):Void;
	@:cffi private static function alDeleteBuffer_wrap (buffer:Dynamic):Void;
	@:cffi private static function alDeleteBuffers_wrap (buffers:Array<ALBufferHandle>):Void;
	@:cffi private static function alDeleteSource_wrap (source:Dynamic):Void;
	@:cffi private static function alDeleteSources_wrap (sources:Array<ALSourceHandle>):Void;
	@:cffi private static function alDisable (capability:Int):Void;
	@:cffi private static function alDistanceModel (distanceModel:Int):Void;
	@:cffi private static function alDopplerFactor (value:Float32):Void;
	@:cffi private static function alDopplerVelocity (value:Float32):Void;
	@:cffi private static function alEnable (capability:Int):Void;
	@:cffi private static function alGetBoolean (param:Int):Bool;
	@:cffi private static function alGetBooleanv_wrap (param:Int, count:Int):Array<Bool>;
	@:cffi private static function alGenBuffer_wrap (context:ALCContextWrapperHandle):ALBufferHandle;
	@:cffi private static function alGenBuffers_wrap (context:ALCContextWrapperHandle, n:Int):Array<ALBufferHandle>;
	@:cffi private static function alGenSource_wrap (context:ALCContextWrapperHandle):ALSourceHandle;
	@:cffi private static function alGenSources_wrap (context:ALCContextWrapperHandle, n:Int):Array<ALSourceHandle>;
	@:cffi private static function alGetBuffer3f_wrap (buffer:ALBufferHandle, param:Int):Dynamic;
	@:cffi private static function alGetBuffer3i_wrap (buffer:ALBufferHandle, param:Int):Dynamic;
	@:cffi private static function alGetBufferf_wrap (buffer:ALBufferHandle, param:Int):Float32;
	@:cffi private static function alGetBufferfv_wrap (buffer:ALBufferHandle, param:Int, count:Int):Dynamic;
	@:cffi private static function alGetBufferi_wrap (buffer:ALBufferHandle, param:Int):Int;
	@:cffi private static function alGetBufferiv_wrap (buffer:ALBufferHandle, param:Int, count:Int):Dynamic;
	@:cffi private static function alGetDouble (param:Int):Float;
	@:cffi private static function alGetDoublev_wrap (param:Int, count:Int):Dynamic;
	@:cffi private static function alGetEnumValue (ename:CString):Int;
	@:cffi private static function alGetError ():Int;
	@:cffi private static function alGetFloat (param:Int):Float32;
	@:cffi private static function alGetFloatv_wrap (param:Int, count:Int):Dynamic;
	@:cffi private static function alGetInteger (param:Int):Int;
	@:cffi private static function alGetIntegerv_wrap (param:Int, count:Int):Dynamic;
	@:cffi private static function alGetListener3f_wrap (param:Int):Dynamic;
	@:cffi private static function alGetListener3i_wrap (param:Int):Dynamic;
	@:cffi private static function alGetListenerf_wrap (param:Int):Float32;
	@:cffi private static function alGetListenerfv_wrap (param:Int, count:Int):Dynamic;
	@:cffi private static function alGetListeneri_wrap (param:Int):Int;
	@:cffi private static function alGetListeneriv_wrap (param:Int, count:Int):Dynamic;
	@:cffi private static function alGetSource3f_wrap (source:ALSourceHandle, param:Int):Dynamic;
	@:cffi private static function alGetSource3i_wrap (source:ALSourceHandle, param:Int):Dynamic;
	@:cffi private static function alGetSourcef_wrap (source:ALSourceHandle, param:Int):Float32;
	@:cffi private static function alGetSourcefv_wrap (source:ALSourceHandle, param:Int, count:Int):Dynamic;
	@:cffi private static function alGetSourcei_wrap (source:ALSourceHandle, param:Int):Int;
	@:cffi private static function alGetSourceiv_wrap (source:ALSourceHandle, param:Int, count:Int):Dynamic;
	@:cffi private static function alGetString (param:Int):CString;
	@:cffi private static function alIsBuffer_wrap (buffer:ALBufferHandle):Bool;
	@:cffi private static function alIsEnabled (capability:Int):Bool;
	@:cffi private static function alIsExtensionPresent (extname:CString):Bool;
	@:cffi private static function alIsSource_wrap (source:ALSourceHandle):Bool;
	@:cffi private static function alListener3f (param:Int, value1:Float32, value2:Float32, value3:Float32):Void;
	@:cffi private static function alListener3i (param:Int, value1:Int, value2:Int, value3:Int):Void;
	@:cffi private static function alListenerf (param:Int, value1:Float32):Void;
	@:cffi private static function alListenerfv_wrap (param:Int, values:HxVector_Float):Void;
	@:cffi private static function alListeneri (param:Int, value1:Int):Void;
	@:cffi private static function alListeneriv_wrap (param:Int, values:HxVector_Int):Void;
	@:cffi private static function alSource3f_wrap (source:ALSourceHandle, param:Int, value1:Float32, value2:Float32, value3:Float32):Void;
	@:cffi private static function alSource3i_wrap (source:ALSourceHandle, param:Int, value1:Int, value2:Int, value3:Int):Void;
	@:cffi private static function alSourceBuffer (source:ALSourceHandle, buffer:CFFIPointer):Void;
	@:cffi private static function alSourcePause_wrap (source:ALSourceHandle):Void;
	@:cffi private static function alSourcePausev_wrap (sources:Array<ALSourceHandle>):Void;
	@:cffi private static function alSourcePlay_wrap (source:ALSourceHandle):Void;
	@:cffi private static function alSourcePlayv_wrap (sources:Array<ALSourceHandle>):Void;
	@:cffi private static function alSourceQueueBuffers_wrap (source:ALSourceHandle, nb:Int, buffers:Array<ALBufferHandle>):Void;
	@:cffi private static function alSourceRewind_wrap (source:ALSourceHandle):Void;
	@:cffi private static function alSourceRewindv_wrap (sources:Array<ALSourceHandle>):Void;
	@:cffi private static function alSourceStop_wrap (source:ALSourceHandle):Void;
	@:cffi private static function alSourceStopv_wrap (sources:Array<ALSourceHandle>):Void;
	@:cffi private static function alSourceUnqueueBuffers_wrap (source:ALSourceHandle, nb:Int):Dynamic;
	@:cffi private static function alSourcef_wrap (source:ALSourceHandle, param:Int, value:Float32):Void;
	@:cffi private static function alSourcefv_wrap (source:ALSourceHandle, param:Int, values:HxVector_Float):Void;
	@:cffi private static function alSourcei_wrap (source:ALSourceHandle, param:Int, value:Int):Void;
	@:cffi private static function alSourceiv_wrap (source:ALSourceHandle, param:Int, values:HxVector_Int):Void;
	@:cffi private static function alSpeedOfSound (speed:Float32):Void;
	#end
	
	
}