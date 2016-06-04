using Android.App;
using Android.Content.PM;
using System;
using System.Reflection;

namespace ::APP_PACKAGE::
{
    [Activity(Label = "::APP_TITLE::", Name="::APP_PACKAGE::.MainActivity",
        ConfigurationChanges = ConfigChanges.KeyboardHidden | ConfigChanges.Orientation | ConfigChanges.ScreenSize | ConfigChanges.ScreenLayout,
        MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Org.Haxe.Lime.GameActivity
    {
        class MainRunnable : Java.Lang.Object, Java.Lang.IRunnable
        {
            public void Run()
            {
                AppDomain domain = AppDomain.CreateDomain("ApplicationMainDomain");

                Assembly asm = Assembly.Load("ApplicationMain.dll");
                System.Type ndllType = asm.GetType("cs.ndll.NDLLFunction");
                FieldInfo libDirField = ndllType.GetField("LibraryDir");
                FieldInfo libPrefixField = ndllType.GetField("LibraryPrefix");
                FieldInfo libSuffixField = ndllType.GetField("LibrarySuffix");

                System.Type appMainType = asm.GetType("ApplicationMain");
                MethodInfo mainMethod = appMainType.GetMethod("main");

                libDirField.SetValue(null, MainActivity.MSingleton.ApplicationInfo.NativeLibraryDir);
                libPrefixField.SetValue(null, "lib");
                libSuffixField.SetValue(null, ".so");
                
                Java.Lang.String[] sdlArgs = {};
                NativeInit(sdlArgs);
                string[] mainArgs = {};
                mainMethod.Invoke(null, mainArgs);

                AppDomain.Unload(domain);
            }
        }

        public override Java.Lang.IRunnable CreateRunnable()
        {
            return new MainRunnable();
        }
    }
}

