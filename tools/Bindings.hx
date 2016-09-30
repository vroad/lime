import haxe.macro.Expr;
import lime._backend.native.NativeApplication;
import lime._backend.native.NativeMouse;
import lime._backend.native.NativeRenderer;
import lime._backend.native.opengl.RenderingContext;
import lime.graphics.cairo.Cairo;
import lime.graphics.cairo.CairoFontFace;
import lime.graphics.cairo.CairoFTFontFace;
import lime.net.curl.CURL;
import lime.net.curl.CURLEasy;
import lime.system.CFFI;
import lime.text.TextLayout;
import lime.ui.Gamepad;
import lime.ui.Joystick;
import lime.utils.compress.Deflate;
import lime.utils.compress.GZip;
import lime.utils.compress.LZMA;
import lime.utils.compress.Zlib;
import sys.FileSystem;
import sys.io.File;

class Bindings {
	
	static macro function generateFileList ():Expr {
		
		var xml = Xml.createDocument ();
		var xmlElement = Xml.createElement ("xml");
		xml.addChild (xmlElement);
		var filesElement = Xml.createElement ("files");
		filesElement.set ("id", "bindings");
		xmlElement.addChild (filesElement);
		filesElement.addChild (createCompilerFlagElement ("-Iinclude"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/cairo/include"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/openal/include/", null, "emscripten"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/default/", null, "windows || mac || linux || rpi"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/linux/", "linux", "rpi"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/windows/", "windows"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/mac/", "mac"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/rpi/", "rpi"));
		filesElement.addChild (createCompilerFlagElement ("-DLIME_CAIRO"));
		filesElement.addChild (createCompilerFlagElement ("-DHAVE_CONFIG_H"));
		filesElement.addChild (createCompilerFlagElement ("-DCAIRO_WIN32_STATIC_BUILD", "windows"));
		filesElement.addChild (createCompilerFlagElement ("-DCAIRO_HAS_FT_FONT"));
		filesElement.addChild (createCompilerFlagElement ("-DLIME_OPENAL"));
		filesElement.addChild (createCompilerFlagElement ("-DLIME_OPENALSOFT"));
		filesElement.addChild (createCompilerFlagElement ("-DAL_LIBTYPE_STATIC=1"));
		filesElement.addChild (createCompilerFlagElement ("-DAL_ALEXT_PROTOTYPES"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/curl/include/"));
		filesElement.addChild (createCompilerFlagElement ("-DLIME_CURL"));
		filesElement.addChild (createCompilerFlagElement ("-DCURL_STATICLIB"));
		
		for (file in CFFI.files) {
			
			var fileElement = Xml.createElement ("file");
			fileElement.set ("name", "bindings/" + file);
			filesElement.addChild (fileElement);
			
		}
		
		var fileName = "../project/bindings/files.xml";
		File.saveContent (fileName, xml.toString ());
		return macro {};
		
	}
	
	static function createCompilerFlagElement (value:String, ifExpr:String = null, unlessExpr:String = null):Xml {
		
		var elem = Xml.createElement ("compilerflag");
		elem.set ("value", value);
		
		if (ifExpr != null) {
			
			elem.set ("if", ifExpr);
			
		}
		
		if (unlessExpr != null) {
			
			elem.set ("unless", unlessExpr);
			
		}
		
		return elem;
		
	}
	
	static function main ():Void {
		
		generateFileList ();
		
	}
	
}