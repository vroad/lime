import haxe.macro.Expr;
import lime._backend.native.bindings.ApplicationWrap;
import lime.system.CFFI;
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
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/boost"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/default/", null, "windows || mac || linux || rpi"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/linux/", "linux", "rpi"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/windows/", "windows"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/mac/", "mac"));
		filesElement.addChild (createCompilerFlagElement ("-I${NATIVE_TOOLKIT_PATH}/sdl/include/configs/rpi/", "rpi"));
		
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