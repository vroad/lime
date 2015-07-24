package;

#if codegen
import haxe.crypto.HashMethod;
import haxe.crypto.Sha256;
import haxe.Timer;
#end

import lime.app.Application;
import lime.app.Config;
import lime.app.Event;
import lime.app.Module;
import lime.app.Preloader;
import lime.audio.openal.AL;
import lime.audio.openal.ALC;
import lime.audio.openal.ALContext;
import lime.audio.openal.ALDevice;
import lime.audio.ALAudioContext;
import lime.audio.ALCAudioContext;
import lime.audio.AudioBuffer;
import lime.audio.AudioContext;
import lime.audio.AudioManager;
import lime.audio.AudioSource;
import lime.audio.FlashAudioContext;
import lime.audio.HTML5AudioContext;
import lime.audio.WebAudioContext;
import lime.graphics.format.BMP;
import lime.graphics.format.JPEG;
import lime.graphics.format.PNG;
import lime.graphics.opengl.GL;
import lime.graphics.opengl.GLActiveInfo;
import lime.graphics.opengl.GLBuffer;
import lime.graphics.opengl.GLContextAttributes;
import lime.graphics.opengl.GLFramebuffer;
import lime.graphics.opengl.GLObject;
import lime.graphics.opengl.GLProgram;
import lime.graphics.opengl.GLRenderbuffer;
import lime.graphics.opengl.GLShader;
import lime.graphics.opengl.GLShaderPrecisionFormat;
import lime.graphics.opengl.GLTexture;
import lime.graphics.opengl.GLUniformLocation;
import lime.graphics.utils.ImageCanvasUtil;
import lime.graphics.utils.ImageDataUtil;
import lime.graphics.CanvasRenderContext;
import lime.graphics.DOMRenderContext;
import lime.graphics.FlashRenderContext;
import lime.graphics.GLRenderContext;
import lime.graphics.Image;
import lime.graphics.ImageBuffer;
import lime.graphics.ImageType;
import lime.graphics.RenderContext;
import lime.graphics.Renderer;
//import lime.graphics.TextFormat;
import lime.math.ColorMatrix;
import lime.math.Matrix3;
import lime.math.Matrix4;
import lime.math.Rectangle;
import lime.math.Vector2;
import lime.math.Vector4;
import lime.net.curl.CURL;
import lime.net.curl.CURLCode;
import lime.net.curl.CURLEasy;
import lime.net.curl.CURLInfo;
import lime.net.curl.CURLOption;
import lime.net.curl.CURLVersion;
import lime.net.oauth.OAuthClient;
import lime.net.oauth.OAuthConsumer;
import lime.net.oauth.OAuthRequest;
import lime.net.oauth.OAuthSignatureMethod;
import lime.net.oauth.OAuthToken;
import lime.net.oauth.OAuthVersion;
//import lime.net.NetConnection;
//import lime.net.NetConnectionManager;
import lime.net.URIParser;
import lime.net.URLLoader;
import lime.net.URLLoaderDataFormat;
import lime.net.URLRequest;
import lime.net.URLRequestHeader;
import lime.net.URLRequestMethod;
import lime.net.URLVariables;
#if ((windows || mac || linux || neko) && !codegen)
import lime.project.ApplicationData;
import lime.project.Architecture;
import lime.project.Asset;
import lime.project.AssetEncoding;
import lime.project.AssetType;
import lime.project.Command;
import lime.project.ConfigData;
import lime.project.Dependency;
import lime.project.HXProject;
import lime.project.Haxelib;
import lime.project.Icon;
import lime.project.Keystore;
import lime.project.Library;
import lime.project.NDLL;
import lime.project.NDLLType;
import lime.project.Orientation;
import lime.project.Platform;
import lime.project.PlatformTarget;
import lime.project.PlatformType;
import lime.project.ProjectXMLParser;
import lime.project.SplashScreen;
import lime.project.WindowData;
#end
import lime.system.System;
import lime.system.ThreadPool;
import lime.system.ThreadPoolMessage;
import lime.system.ThreadPoolMessageType;
import lime.text.Font;
import lime.text.TextDirection;
import lime.text.TextLayout;
import lime.text.TextScript;
#if ((windows || mac || linux || neko) && !codegen)
import lime.tools.helpers.AIRHelper;
import lime.tools.helpers.AndroidHelper;
import lime.tools.helpers.AntHelper;
import lime.tools.helpers.ArrayHelper;
import lime.tools.helpers.AssetHelper;
import lime.tools.helpers.BlackBerryHelper;
import lime.tools.helpers.CLIHelper;
import lime.tools.helpers.CPPHelper;
import lime.tools.helpers.CompatibilityHelper;
import lime.tools.helpers.CordovaHelper;
import lime.tools.helpers.FileHelper;
import lime.tools.helpers.FlashHelper;
import lime.tools.helpers.HTML5Helper;
import lime.tools.helpers.IOSHelper;
import lime.tools.helpers.IconHelper;
import lime.tools.helpers.ImageHelper;
import lime.tools.helpers.JavaHelper;
import lime.tools.helpers.LogHelper;
import lime.tools.helpers.NekoHelper;
import lime.tools.helpers.NodeJSHelper;
import lime.tools.helpers.ObjectHelper;
import lime.tools.helpers.PathHelper;
import lime.tools.helpers.PlatformHelper;
import lime.tools.helpers.ProcessHelper;
import lime.tools.helpers.StringHelper;
import lime.tools.helpers.StringMapHelper;
import lime.tools.helpers.TizenHelper;
import lime.tools.helpers.WebOSHelper;
import lime.tools.helpers.ZipHelper;
import lime.tools.platforms.AndroidPlatform;
import lime.tools.platforms.BlackBerryPlatform;
import lime.tools.platforms.EmscriptenPlatform;
import lime.tools.platforms.FirefoxPlatform;
import lime.tools.platforms.FlashPlatform;
import lime.tools.platforms.HTML5Platform;
import lime.tools.platforms.IOSPlatform;
import lime.tools.platforms.LinuxPlatform;
import lime.tools.platforms.MacPlatform;
import lime.tools.platforms.TizenPlatform;
import lime.tools.platforms.WebOSPlatform;
import lime.tools.platforms.WindowsPlatform;
#end
import lime.ui.KeyCode;
import lime.ui.Mouse;
import lime.ui.MouseCursor;
import lime.ui.Window;
import lime.utils.ArrayBuffer;
import lime.utils.ArrayBufferView;
import lime.utils.ByteArray;
import lime.utils.Float32Array;
import lime.utils.GLUtils;
import lime.utils.IDataInput;
import lime.utils.IMemoryRange;
import lime.utils.Int16Array;
import lime.utils.Int32Array;
import lime.utils.Int8Array;
import lime.utils.UInt16Array;
import lime.utils.UInt32Array;
import lime.utils.UInt8Array;
//import lime.vm.NekoVM;
import lime.Assets;

#if codegen
class ImportAll
{
	public static function main()
	{
		untyped
		{
			exports.haxe_crypto_HashMethod = haxe_crypto_HashMethod;
			exports.haxe_crypto_Hmac = haxe_crypto_Hmac;
			exports.haxe_crypto_Sha256 = haxe_crypto_Sha256;
			exports.haxe_Timer = haxe_Timer;
			exports.lime_app_Application = lime_app_Application;
			//exports.lime_app_Config = lime_app_Config;
			exports.lime_app_Event = lime_app_Event;
			exports.lime_app_Module = lime_app_Module;
			exports.lime_app_Preloader = lime_app_Preloader;
			exports.lime_audio_openal_AL = lime_audio_openal_AL;
			exports.lime_audio_openal_ALC = lime_audio_openal_ALC;
			//exports.lime_audio_openal_ALContext = lime_audio_openal_ALContext;
			//exports.lime_audio_openal_ALDevice = lime_audio_openal_ALDevice;
			exports.lime_audio_ALAudioContext = lime_audio_ALAudioContext;
			exports.lime_audio_ALCAudioContext = lime_audio_ALCAudioContext;
			exports.lime_audio_AudioBuffer = lime_audio_AudioBuffer;
			exports.lime_audio_AudioContext = lime_audio_AudioContext;
			exports.lime_audio_AudioManager = lime_audio_AudioManager;
			exports.lime_audio_AudioSource = lime_audio_AudioSource;
			exports.lime_audio_FlashAudioContext = lime_audio_FlashAudioContext;
			exports.lime_audio_HTML5AudioContext = lime_audio_HTML5AudioContext;
			exports.lime_audio_WebAudioContext = lime_audio_WebAudioContext;
			exports.lime_graphics_format_BMP = lime_graphics_format_BMP;
			exports.lime_graphics_format_JPEG = lime_graphics_format_JPEG;
			exports.lime_graphics_format_PNG = lime_graphics_format_PNG;
			//exports.lime_graphics_opengl_GL = lime_graphics_opengl_GL;
			//exports.lime_graphics_opengl_GLActiveInfo = lime_graphics_opengl_GLActiveInfo;
			exports.lime_graphics_opengl_GLBuffer = lime_graphics_opengl_GLBuffer;
			//exports.lime_graphics_opengl_GLContextAttributes = lime_graphics_opengl_GLContextAttributes;
			exports.lime_graphics_opengl_GLFramebuffer = lime_graphics_opengl_GLFramebuffer;
			exports.lime_graphics_opengl_GLObject = lime_graphics_opengl_GLObject;
			exports.lime_graphics_opengl_GLProgram = lime_graphics_opengl_GLProgram;
			exports.lime_graphics_opengl_GLRenderbuffer = lime_graphics_opengl_GLRenderbuffer;
			exports.lime_graphics_opengl_GLShader = lime_graphics_opengl_GLShader;
			//exports.lime_graphics_opengl_GLShaderPrecisionFormat = lime_graphics_opengl_GLShaderPrecisionFormat;
			exports.lime_graphics_opengl_GLTexture = lime_graphics_opengl_GLTexture;
			//exports.lime_graphics_opengl_GLUniformLocation = lime_graphics_opengl_GLUniformLocation;
			exports.lime_graphics_utils_ImageCanvasUtil = lime_graphics_utils_ImageCanvasUtil;
			exports.lime_graphics_utils_ImageDataUtil = lime_graphics_utils_ImageDataUtil;
			exports.lime_graphics_CanvasRenderContext = lime_graphics_CanvasRenderContext;
			exports.lime_graphics_DOMRenderContext = lime_graphics_DOMRenderContext;
			exports.lime_graphics_FlashRenderContext = lime_graphics_FlashRenderContext;
			exports.lime_graphics_GLRenderContext = lime_graphics_GLRenderContext;
			exports.lime_graphics_Image = lime_graphics_Image;
			exports.lime_graphics_ImageBuffer = lime_graphics_ImageBuffer;
			exports.lime_graphics_ImageType = lime_graphics_ImageType;
			exports.lime_graphics_RenderContext = lime_graphics_RenderContext;
			exports.lime_graphics_Renderer = lime_graphics_Renderer;
			//exports.lime_graphics_TextFormat = lime_graphics_TextFormat;
			//exports.lime_math_ColorMatrix = lime_math_ColorMatrix;
			exports.lime_math_Matrix3 = lime_math_Matrix3;
			//exports.lime_math_Matrix4 = lime_math_Matrix4;
			exports.lime_math_Rectangle = lime_math_Rectangle;
			exports.lime_math_Vector2 = lime_math_Vector2;
			//exports.lime_math_Vector4 = lime_math_Vector4;
			//exports.lime_net_curl_CURL = lime_net_curl_CURL;
			//exports.lime_net_curl_CURLCode = lime_net_curl_CURLCode;
			exports.lime_net_curl_CURLEasy = lime_net_curl_CURLEasy;
			//exports.lime_net_curl_CURLInfo = lime_net_curl_CURLInfo;
			//exports.lime_net_curl_CURLOption = lime_net_curl_CURLOption;
			//exports.lime_net_curl_CURLVersion = lime_net_curl_CURLVersion;
			exports.lime_net_oauth_OAuthClient = lime_net_oauth_OAuthClient;
			exports.lime_net_oauth_OAuthConsumer = lime_net_oauth_OAuthConsumer;
			exports.lime_net_oauth_OAuthRequest = lime_net_oauth_OAuthRequest;
			//exports.lime_net_oauth_OAuthSignatureMethod = lime_net_oauth_OAuthSignatureMethod;
			//exports.lime_net_oauth_OAuthToken = lime_net_oauth_OAuthToken;
			//exports.lime_net_oauth_OAuthVersion = lime_net_oauth_OAuthVersion;
			//exports.lime_net_NetConnection = lime_net_NetConnection;
			//exports.lime_net_NetConnectionManager = lime_net_NetConnectionManager;
			exports.lime_net_URIParser = lime_net_URIParser;
			exports.lime_net_URLLoader = lime_net_URLLoader;
			exports.lime_net_URLLoaderDataFormat = lime_net_URLLoaderDataFormat;
			exports.lime_net_URLRequest = lime_net_URLRequest;
			exports.lime_net_URLRequestHeader = lime_net_URLRequestHeader;
			//exports.lime_net_URLRequestMethod = lime_net_URLRequestMethod;
			exports.lime_net_URLVariables = lime_net_URLVariables;

			exports.lime_system_System = lime_system_System;
			exports.lime_text_Font = lime_text_Font;
			//exports.lime_text_TextDirection = lime_text_TextDirection;
			exports.lime_text_TextLayout = lime_text_TextLayout;
			//exports.lime_text_TextScript = lime_text_TextScript;

			//exports.lime_ui_KeyCode = lime_ui_KeyCode;
			exports.lime_ui_Mouse = lime_ui_Mouse;
			exports.lime_ui_MouseCursor = lime_ui_MouseCursor;
			exports.lime_ui_Window = lime_ui_Window;
			//exports.lime_utils_ArrayBuffer = lime_utils_ArrayBuffer;
			//exports.lime_utils_ArrayBufferView = lime_utils_ArrayBufferView;
			exports.lime_utils_ByteArray = lime_utils_ByteArray;
			//exports.lime_utils_Float32Array = lime_utils_Float32Array;
			exports.lime_utils_GLUtils = lime_utils_GLUtils;
			exports.lime_utils_IDataInput = lime_utils_IDataInput;
			exports.lime_utils_IMemoryRange = lime_utils_IMemoryRange;
			//exports.lime_utils_Int16Array = lime_utils_Int16Array;
			//exports.lime_utils_Int32Array = lime_utils_Int32Array;
			//exports.lime_utils_Int8Array = lime_utils_Int8Array;
			//exports.lime_utils_UInt16Array = lime_utils_UInt16Array;
			//exports.lime_utils_UInt32Array = lime_utils_UInt32Array;
			//exports.lime_utils_UInt8Array = lime_utils_UInt8Array;
			//exports.lime_vm_NekoVM = lime_vm_NekoVM;
			exports.lime_Assets = lime_Assets;

			exports.lime_AssetLibrary = lime_AssetLibrary;
		}
	}
}
#end