package lime.tools.helpers;

import lime.tools.helpers.ProcessHelper;
import lime.project.HXProject;
import sys.io.File;

class CSHelper {
	
	
	public static function copyLibraries (templatePaths:Array <String>, platformName:String, targetPath:String) {
		
		FileHelper.recursiveCopyTemplate (templatePaths, "cs/ndll/" + platformName, targetPath);
		
	}
	
	public static function addCSNDLLReference (txtPath:String, csNdllPath:String) {
		
		var content = File.getContent(txtPath);
		content +=
			"begin libs\n" +
			csNdllPath + "\n" +
			"end libs\n";
		File.saveContent (txtPath, content);
		
	}
	
	public static function compile (project:HXProject, path:String, outPath:String, arch:String, buildFile:String = "hxcs_build.txt") {
		
		var args = [ "run", project.config.getString ("cs.buildLibrary", "hxcs"), buildFile, "--arch", arch, "--out", outPath ];
		var code = ProcessHelper.runCommand (path, "haxelib", args);
			
		if (code != 0) {
			
			Sys.exit (code);
			
		}
		
	}
	
	
}
