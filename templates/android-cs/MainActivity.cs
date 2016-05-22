using Android.App;
using Android.OS;
using cs.ndll;
using Org.Libsdl.App;

namespace ::APP_PACKAGE::
{
    [Activity(Label = "::APP_TITLE::", Name="::APP_PACKAGE::.MainActivity", MainLauncher = true, Icon = "@drawable/icon")]
    public class MainActivity : Org.Haxe.Lime.GameActivity
    {
        class MainRunnable : Java.Lang.Object, Java.Lang.IRunnable
        {
            public void Run()
            {
                NDLLFunction.LibraryDir = MainActivity.MSingleton.ApplicationInfo.NativeLibraryDir;
                NDLLFunction.LibraryPrefix = "lib";
                NDLLFunction.LibrarySuffix = ".so";
                
                Java.Lang.String[] arguments = {};
                SDLActivity.NativeInit(arguments);
                ApplicationMain.main();
            }
        }

        public override void OnCreate(Bundle savedInstanceState, PersistableBundle persistentState)
        {
            base.OnCreate(savedInstanceState, persistentState);
        }

        public override Java.Lang.IRunnable CreateRunnable()
        {
            return new MainRunnable();
        }
    }
}

