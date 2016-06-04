package lime.tools.platforms;


import haxe.io.Path;
import haxe.Template;
import lime.tools.helpers.AndroidHelper;
import lime.tools.helpers.ArrayHelper;
import lime.tools.helpers.AssetHelper;
import lime.tools.helpers.CPPHelper;
import lime.tools.helpers.CSHelper;
import lime.tools.helpers.DeploymentHelper;
import lime.tools.helpers.FileHelper;
import lime.tools.helpers.GUID;
import lime.tools.helpers.IconHelper;
import lime.tools.helpers.LogHelper;
import lime.tools.helpers.PathHelper;
import lime.tools.helpers.ProcessHelper;
import lime.project.Architecture;
import lime.project.AssetType;
import lime.project.HXProject;
import lime.project.Icon;
import lime.project.NDLL;
import lime.project.PlatformTarget;
import sys.io.File;
import sys.FileSystem;
using StringTools;

class AndroidPlatform extends PlatformTarget {
	
	
	private var deviceID:String;
	private var targetType:String;
	private var templateDirectory:String;
	private static var iconTypes:Array<String> = [ "ldpi", "mdpi", "hdpi", "xhdpi", "xxhdpi", "xxxhdpi" ];
	private static var csResourceDir:String = "Resources\\";
	private var assetPaths:Array<String>;
	private var appMainGUID:String;
	
	public function new (command:String, _project:HXProject, targetFlags:Map <String, String>) {
		
		super (command, _project, targetFlags);
		
		if (project.targetFlags.exists ("cs")) {
			
			targetType = "cs";
			templateDirectory = "android-cs";
			
		} else {
			
			targetType = "cpp";
			templateDirectory = "android";
			
		}
		
		if (command != "display" && command != "clean") {
			
			project = project.clone ();
			
			if (!project.environment.exists ("ANDROID_SETUP")) {
				
				LogHelper.error ("You need to run \"lime setup android\" before you can use the Android target");
				
			}
			
			AndroidHelper.initialize (project);
			
			if (deviceID == null && project.targetFlags.exists ("device")) {
				
				deviceID = project.targetFlags.get ("device") + ":5555";
				
			}
			
		}
		
		targetDirectory = project.app.path + "/" + templateDirectory;
		assetPaths = [];
		
	}
	
	
	public override function build ():Void {
		
		var destination = targetDirectory + "/bin";
		
		var type = "release";
		
		if (project.debug) {
			
			type = "debug";
			
		} else if (project.targetFlags.exists ("final")) {
			
			type = "final";
			
		}
		
		var hxml = targetDirectory + "/haxe/" + type + ".hxml";
		
		var hasARMV5 = (ArrayHelper.containsValue (project.architectures, Architecture.ARMV5) || ArrayHelper.containsValue (project.architectures, Architecture.ARMV6));
		var hasARMV7 = ArrayHelper.containsValue (project.architectures, Architecture.ARMV7);
		var hasX86 = ArrayHelper.containsValue (project.architectures, Architecture.X86);
		
		var architectures = [];
		
		if (hasARMV5) architectures.push (Architecture.ARMV5);
		if (hasARMV7) architectures.push (Architecture.ARMV7);
		if (hasX86) architectures.push (Architecture.X86);
		
		var libDir;
		if (targetType == "cs") {
			
			libDir = targetDirectory + "/obj/Libraries";
			
		} else {
			
			libDir = targetDirectory + "/bin/libs";
			
		}
		
		if (architectures.length == 0) {
			
			throw "No CPU architecture specified in project";
			
		}
		
		for (architecture in architectures) {
			
			var haxeParams = [ hxml, "-D", "android", "-D", "android-9" ];
			var cppParams = [ "-Dandroid", "-Dandroid-9" ];
			var path = libDir + "/armeabi";
			var suffix = ".so";
			
			if (architecture == Architecture.ARMV7) {
				
				haxeParams.push ("-D");
				haxeParams.push ("HXCPP_ARMV7");
				cppParams.push ("-DHXCPP_ARMV7");
				path = libDir + "/armeabi-v7a";
				suffix = "-v7.so";
				
			} else if (architecture == Architecture.X86) {
				
				haxeParams.push ("-D");
				haxeParams.push ("HXCPP_X86");
				cppParams.push ("-DHXCPP_X86");
				path = libDir + "/x86";
				suffix = "-x86.so";
				
			}
			
			for (ndll in project.ndlls) {
				
				FileHelper.copyLibrary (project, ndll, "Android", "lib", suffix, path, project.debug, ".so");
				
			}
			
			if (targetType == "cpp") {
				
				ProcessHelper.runCommand ("", "haxe", haxeParams);
				CPPHelper.compile (project, targetDirectory + "/obj", cppParams);
				FileHelper.copyIfNewer (targetDirectory + "/obj/libApplicationMain" + (project.debug ? "-debug" : "") + suffix, path + "/libApplicationMain.so");
				
			}
			
		}
		
		if (!hasARMV5) {
			
			if (FileSystem.exists (libDir + "/armeabi")) {
				
				PathHelper.removeDirectory (libDir + "/armeabi");
				
			}
			
		}
		
		if (!hasARMV7) {
			
			if (FileSystem.exists (libDir + "/armeabi-v7a")) {
				
				PathHelper.removeDirectory (libDir + "/armeabi-v7a");
				
			}
			
		}
		
		if (!hasX86) {
			
			if (FileSystem.exists (libDir + "/x86")) {
				
				PathHelper.removeDirectory (libDir + "/x86");
				
			}
			
		}
		
		if (targetType == "cs") {
			
			ProcessHelper.runCommand ("", "haxe", [hxml, "-D", "android"]);
			CSHelper.copySourceFiles (project.templatePaths, targetDirectory + "/obj/src");
			//FileHelper.copyFileTemplate (project.templatePaths, templateDirectory + "/MainActivity.cs", targetDirectory + "/obj/src/MainActivity.cs", project.templateContext);
			FileHelper.copyFileTemplate (project.templatePaths, templateDirectory + "/AssemblyInfo.cs", targetDirectory + "/obj/src/AssemblyInfo.cs", project.templateContext);
			var txtPath = targetDirectory + "/obj/hxcs_build.txt";
			var resources = getResourcePaths (csResourceDir);
			var sourceFiles = CSHelper.ndllSourceFiles.copy ();
			//sourceFiles.push ("MainActivity");
			sourceFiles.push ("AssemblyInfo");
			CSHelper.addSourceFiles (txtPath, sourceFiles);
			
			#if 0
			CSHelper.addAndroidResources (txtPath, resources);
			CSHelper.addAssemblies (txtPath, [FileSystem.absolutePath(targetDirectory + "/obj/GameActivity\\bin\\Release\\Org.Haxe.Lime.GameActivity.dll")]);
			CSHelper.addAndroidABIs (txtPath, architectures);
			CSHelper.addNativeLibraries (txtPath, targetDirectory + "/obj/Libraries/", project.ndlls, architectures);
			CSHelper.addAssets (txtPath, assetPaths);
			#end
			CSHelper.addGUID (txtPath, appMainGUID);
			
			CSHelper.buildGradleProj (targetDirectory + "/obj/GameActivity/gameactivity");
			//CSHelper.buildCSProj (targetDirectory + "/obj", targetDirectory + "/obj/GameActivity/GameActivity.csproj");
			CSHelper.compile (project, targetDirectory + "/obj", targetDirectory +  "/obj/ApplicationMain", "anycpu", "android", true);
			//CSHelper.buildCSProj (targetDirectory + "/obj", targetDirectory + "/obj/ApplicationMain.csproj");
			CSHelper.buildSln (targetDirectory + "/obj", targetDirectory + "/obj/MainActivity.sln");
			CSHelper.buildCSProj (targetDirectory + "/obj", targetDirectory + "/obj/MainActivity.csproj", "SignAndroidPackage");
			
			FileHelper.copyIfNewer (targetDirectory + "/obj/bin/" + (project.debug ? "Debug" : "Release") + "/" + project.meta.packageName + "-Signed.apk",
				targetDirectory + "/bin/" + project.app.file + "-debug.apk");
				
		}
		
		if (targetType == "cs") {
			
			
			
		} else {
			
			AndroidHelper.build (project, destination);
			
		}
		
	}
	
	
	public override function clean ():Void {
		
		if (FileSystem.exists (targetDirectory)) {
			
			PathHelper.removeDirectory (targetDirectory);
			
		}
		
	}
	
	
	public override function deploy ():Void {
		
		DeploymentHelper.deploy (project, targetFlags, targetDirectory, "Android");
		
	}
	
	
	public override function display ():Void {
		
		var type = "release";
		
		if (project.debug) {
			
			type = "debug";
			
		} else if (project.targetFlags.exists ("final")) {
			
			type = "final";
			
		}
		
		var hxml = PathHelper.findTemplate (project.templatePaths, templateDirectory + "/hxml/" + type + ".hxml");
		
		var context = project.templateContext;
		context.CPP_DIR = targetDirectory + "/obj";
		
		var template = new Template (File.getContent (hxml));
		
		Sys.println (template.execute (context));
		Sys.println ("-D display");
		
	}
	
	
	public override function install ():Void {
		
		var build = "debug";
		
		if (project.certificate != null) {
			
			build = "release";
			
		}
		
		var binDir;
		var apkName;
		
		if (targetType == "cs") {
			
			binDir = "/bin/";
			apkName = project.app.file + "-" + build + ".apk";
			
		} else {
			
			binDir = "/bin/bin/";
			apkName = project.app.file + "-" + build + ".apk";
			
		}
		
		deviceID = AndroidHelper.install (project, FileSystem.fullPath (targetDirectory) + binDir + apkName, deviceID);
		
	}
	
	
	public override function rebuild ():Void {
		
		var armv5 = (command == "rebuild" || ArrayHelper.containsValue (project.architectures, Architecture.ARMV5) || ArrayHelper.containsValue (project.architectures, Architecture.ARMV6));
		var armv7 = (command == "rebuild" || ArrayHelper.containsValue (project.architectures, Architecture.ARMV7));
		var x86 = (command == "rebuild" || ArrayHelper.containsValue (project.architectures, Architecture.X86));
		
		var commands = [];
		
		if (armv5) commands.push ([ "-Dandroid", "-DPLATFORM=android-9" ]);
		if (armv7) commands.push ([ "-Dandroid", "-DHXCPP_ARMV7", "-DHXCPP_ARM7", "-DPLATFORM=android-9" ]);
		if (x86) commands.push ([ "-Dandroid", "-DHXCPP_X86", "-DPLATFORM=android-9" ]);
		
		CPPHelper.rebuild (project, commands);
		
	}
	
	
	public override function run ():Void {
		
		AndroidHelper.run (project.meta.packageName + "/" + project.meta.packageName + ".MainActivity", deviceID);
		
	}
	
	
	public override function trace ():Void {
		
		AndroidHelper.trace (project, project.debug, deviceID);
		
	}
	
	
	public override function uninstall ():Void {
		
		AndroidHelper.uninstall (project.meta.packageName, deviceID);
		
	}
	
	
	public override function update ():Void {
		
		project = project.clone ();
		
		for (asset in project.assets) {
			
			if (asset.embed && asset.sourcePath == "") {
				
				var path = PathHelper.combine (targetDirectory + "/obj/tmp", asset.targetPath);
				PathHelper.mkdir (Path.directory (path));
				FileHelper.copyAsset (asset, path);
				asset.sourcePath = path;
				
			}
			
		}
		
		//initialize (project);
		
		var destination;
		var assetDir;
		var resourceDir;
		
		if (targetType == "cs") {
			
			destination = targetDirectory + "/obj/";
			assetDir = destination + "Assets/";
			resourceDir = "/Resources/";
			
		} else {
			
			destination = targetDirectory + "/bin/";
			assetDir = destination + "assets/";
			resourceDir = "/res/";
			
		}
		trace(assetDir);
		
		PathHelper.mkdir (destination);
		PathHelper.mkdir (destination + resourceDir + "drawable-ldpi/");
		PathHelper.mkdir (destination + resourceDir + "drawable-mdpi/");
		PathHelper.mkdir (destination + resourceDir + "drawable-hdpi/");
		PathHelper.mkdir (destination + resourceDir + "drawable-xhdpi/");
		
		assetPaths = [];
		for (asset in project.assets) {
			
			if (asset.type != AssetType.TEMPLATE) {
				
				var targetPath = "";
				
				switch (asset.type) {
					
					default:
					//case SOUND, MUSIC:
						
						//var extension = Path.extension (asset.sourcePath);
						//asset.flatName += ((extension != "") ? "." + extension : "");
						
						//asset.resourceName = asset.flatName;
						targetPath = PathHelper.combine (assetDir, asset.resourceName);
						
						//asset.resourceName = asset.id;
						//targetPath = destination + resourceDir + "raw/" + asset.flatName + "." + Path.extension (asset.targetPath);
					
					//default:
						
						//asset.resourceName = asset.flatName;
						//targetPath = assetDir + asset.resourceName;
					
				}
				
				FileHelper.copyAssetIfNewer (asset, targetPath);
				assetPaths.push(targetPath);
				
			}
			
		}
		
		if (project.targetFlags.exists ("xml")) {
			
			project.haxeflags.push ("-xml " + targetDirectory + "/types.xml");
			
		}
		
		var context = project.templateContext;
		
		context.CPP_DIR = targetDirectory + "/obj";
		context.ANDROID_INSTALL_LOCATION = project.config.getString ("android.install-location", "auto");
		context.ANDROID_MINIMUM_SDK_VERSION = project.config.getInt ("android.minimum-sdk-version", 9);
		context.ANDROID_TARGET_SDK_VERSION = project.config.getInt ("android.target-sdk-version", 19);
		context.ANDROID_EXTENSIONS = project.config.getArrayString ("android.extension");
		context.ANDROID_PERMISSIONS = project.config.getArrayString ("android.permission", [ "android.permission.WAKE_LOCK", "android.permission.INTERNET", "android.permission.VIBRATE", "android.permission.ACCESS_NETWORK_STATE" ]);
		context.ANDROID_LIBRARY_PROJECTS = [];
		
		if (Reflect.hasField (context, "KEY_STORE")) context.KEY_STORE = StringTools.replace (context.KEY_STORE, "\\", "\\\\");
		if (Reflect.hasField (context, "KEY_STORE_ALIAS")) context.KEY_STORE_ALIAS = StringTools.replace (context.KEY_STORE_ALIAS, "\\", "\\\\");
		if (Reflect.hasField (context, "KEY_STORE_PASSWORD")) context.KEY_STORE_PASSWORD = StringTools.replace (context.KEY_STORE_PASSWORD, "\\", "\\\\");
		if (Reflect.hasField (context, "KEY_STORE_ALIAS_PASSWORD")) context.KEY_STORE_ALIAS_PASSWORD = StringTools.replace (context.KEY_STORE_ALIAS_PASSWORD, "\\", "\\\\");
		
		var index = 1;
		
		for (dependency in project.dependencies) {
			
			if (dependency.path != "" && FileSystem.exists (dependency.path) && FileSystem.isDirectory (dependency.path) && FileSystem.exists (PathHelper.combine (dependency.path, "project.properties"))) {
				
				var name = dependency.name;
				if (name == "") name = "project" + index;
				
				context.ANDROID_LIBRARY_PROJECTS.push ({ name: name, index: index, path: "deps/" + name, source: dependency.path });
				index++;
				
			}
			
		}
		
		var iconSizes = [ 36, 48, 72, 96, 144, 192 ];
		var icons = project.icons;
		
		if (icons.length == 0) {
			
			icons = [ new Icon (PathHelper.findTemplate (project.templatePaths, "default/icon.svg")) ];
			
		}
		
		for (i in 0...iconTypes.length) {
			
			if (IconHelper.createIcon (icons, iconSizes[i], iconSizes[i], destination + resourceDir + "drawable-" + iconTypes[i] + "/icon.png")) {
				
				context.HAS_ICON = true;
				
			}
			
		}
		
		IconHelper.createIcon (icons, 732, 412, destination + resourceDir + "drawable-xhdpi/ouya_icon.png");
		
		var packageDirectory = project.meta.packageName;
		packageDirectory = destination + "/src/" + packageDirectory.split (".").join ("/");
		PathHelper.mkdir (packageDirectory);
		
		for (javaPath in project.javaPaths) {
			
			try {
				
				if (FileSystem.isDirectory (javaPath)) {
					
					FileHelper.recursiveCopy (javaPath, destination + "/src", context, true);
					
				} else {
					
					if (Path.extension (javaPath) == "jar") {
						
						FileHelper.copyIfNewer (javaPath, destination + "/libs/" + Path.withoutDirectory (javaPath));
						
					} else {
						
						FileHelper.copyIfNewer (javaPath, destination + "/src/" + Path.withoutDirectory (javaPath));
						
					}
					
				}
				
			} catch (e:Dynamic) {}
				
			//	throw"Could not find javaPath " + javaPath +" required by extension."; 
				
			//}
			
		}
		
		for (library in context.ANDROID_LIBRARY_PROJECTS) {
			
			FileHelper.recursiveCopy (library.source, destination + "/deps/" + library.name, context, true);
			
		}
		
		if (targetType == "cs") {
			
			var gameActivityGUID = GUID.uuid ();
			this.appMainGUID = GUID.uuid ();
			var mainActivityGUID = GUID.uuid ();
			var assetPaths:Array<String> = project.assets.map (
				
				function (v):String {
					
					return PathHelper.combine ("Assets/", v.resourceName).replace ("/", "\\");
					
				}
				
			);
			assetPaths.push ("Assets\\manifest");
			
			context.GAME_ACTIVITY_GUID = gameActivityGUID;
			context.APP_MAIN_GUID = appMainGUID;
			context.MAIN_ACTIVITY_GUID = mainActivityGUID; 
			context.GAME_ACTIVITY_GUID_LOWER = gameActivityGUID.toLowerCase ();
			context.APP_MAIN_GUID_LOWER = appMainGUID.toLowerCase ();
			context.ANDROID_ABIS = CSHelper.getAndroidABINames (project.architectures);
			context.REFS = [];
			context.SRCS = ["Sources\\MainActivity.cs"];
			context.RES = [];
			context.ANDROID_RESOURCES = getResourcePaths (csResourceDir);
			context.ANDROID_ASSETS = assetPaths;
			context.ANDROID_NATIVE_LIBS = CSHelper.getAndroidNativeLibraryPaths (targetDirectory + "/obj/Libraries/", project.ndlls, project.architectures);
			
		}
		
		FileHelper.recursiveCopyTemplate (project.templatePaths, templateDirectory + "/template", destination, context);
		
		if (targetType == "cs") {
			
			//FileHelper.copyFileTemplate (project.templatePaths, templateDirectory + "/MainActivity.cs", destination + "src/MainActivity.cs", context);
			
		} else {
			
			FileHelper.copyFileTemplate (project.templatePaths, templateDirectory + "/MainActivity.java", packageDirectory + "/MainActivity.java", context);
			
		}
		
		FileHelper.recursiveCopyTemplate (project.templatePaths, "haxe", targetDirectory + "/haxe", context);
		FileHelper.recursiveCopyTemplate (project.templatePaths, templateDirectory + "/hxml", targetDirectory + "/haxe", context);
		
		for (asset in project.assets) {
			
			if (asset.type == AssetType.TEMPLATE) {
				
				var targetPath = PathHelper.combine (destination, asset.targetPath);
				PathHelper.mkdir (Path.directory (targetPath));
				FileHelper.copyAsset (asset, targetPath, context);
				
			}
			
		}
		
		AssetHelper.createManifest (project, assetDir + "manifest");
		assetPaths.push(assetDir + "manifest");
		
	}
	
	
	private static function getResourcePaths (resourceDir:String):Array<String> {
		
		var resources = [];
		
		for (iconType in iconTypes) {
			
			resources.push (resourceDir + "drawable-" + iconType + "\\icon.png");
			
		}
		
		resources.push (resourceDir + "drawable-xhdpi\\ouya_icon.png");
		return resources;
		
	}
	
}