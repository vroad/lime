package lime.tools.helpers;

import lime.tools.helpers.ProcessHelper;
import lime.project.HXProject;
import sys.io.File;

class CSHelper {
	
	
	public static function copySourceFiles (templatePaths:Array <String>, targetPath:String) {
		
		FileHelper.recursiveCopyTemplate (templatePaths, "cs/src", targetPath);
		
	}
	
	public static function addCSNDLLReference (txtPath:String) {
		
		var content = File.getContent(txtPath);
		var files = [
				"cs.ndll.NDLLFunction",
				"cs.ndll.CFFICSLoader",
				"cs.ndll.CSAbstract",
				"cs.ndll.CSHandleContainer",
				"cs.ndll.CSHandleScope",
				"cs.ndll.CSPersistent",
				"cs.ndll.DelegateConverter",
				"cs.ndll.HandleUtils",
				"cs.ndll.NativeMethods",
				"cs.ndll.NDLLFunction",
			];
		content += "\nbegin modules\n";
		
		for (file in files) {
			
			content += 'M $file\nC $file\n';
			
		}
		
		content += "end modules\n";
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
