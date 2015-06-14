package lime.app;

#if flash
typedef ApplicationBackend = lime._backend.flash.FlashApplication;
#elseif (js && html5)
typedef ApplicationBackend = lime._backend.html5.HTML5Application;
#else
typedef ApplicationBackend = lime._backend.native.NativeApplication;
#end