package lime.ui;

#if flash
typedef WindowBackend = lime._backend.flash.FlashWindow;
#elseif (js && html5)
typedef WindowBackend = lime._backend.html5.HTML5Window;
#else
typedef WindowBackend = lime._backend.native.NativeWindow;
#end