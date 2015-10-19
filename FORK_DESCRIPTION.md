This file describes the purpose of this fork.

nodejs support
--------------
Making many changes to make lime compatible with nodejs.

Shared code support on nodejs
-----------------------------
This version of lime can be built as a precompiled JavaScript file on nodejs.
More detailed description coming soon at https://bitbucket.org/vroad/haxe-codegen

disable_gl_renderer compile option
---------------------------------------
This flag was made for avoiding OpenGL render state conficts on Stage3D. Works on native and html5.
Only Stage3D API make OpenGL calls if this option is enabled in project.xml.

Streaming support on native
---------------------------
AudioBuffer can be loaded with streaming enabled. Currently limited to Ogg Vorbis.

Faster font rendering
---------------------
Font class can render glyphs without copying output buffer many times.

Faster font loading on Android
------------------------------
Font class does not make copy of file content on loading.

Better handling of native pointers
----------------------------------
NativePointer class in cpp side automatically installs finalizer so that you don't need to call val_gc() manually.
Since this is a template class, you can directly obtain the pointer without manually casting it.

Thread safety
-------------
Trying to make CFFI APIs thread safe by isolating string IDs.

Windows Media Foundation (WMF) support
--------------------------------------
You can decode video with hardware acceleration and render into an texture. Currently limited to ANGLE.

Crash fixes for Android
-----------------------
Fixed JPEG/PNG/Ogg loading issues on Android.

AudioMix wakelock fix for Android
---------------------------------
Automatically stops audio processing when your app goes to background.

Vsync is enabled on ANGLE
---------------------
SDL_GL_SetSwapInterval is enabled as it doesn't seem to have problems.

Other notable changes
-------------
- Do not define DYNAMIC_OGL when ANGLE is not enabled, so that gDEBugger works
