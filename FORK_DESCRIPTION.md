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
Font class renders glyphs without copying many times.

Better handling of native pointers
----------------------------------
NativePointer class in cpp side automatically installs finalizer so that you don't need to call val_gc() manually.
Since this is a template class, you can directly obtain the pointer without manually casting it.

Thread safety
-------------
Trying to make CFFI APIs thread safe by isolating string IDs.

Window-mode vsync fix on Intel HD Graphics
------------------------------
SDL backend uses DwmFlush for vsync when vsync is not force-enabled.

Other changes
-------------
- Only call OpenAL functions on native
- Do not use process.exit() on nodejs as it force closes the app
- Do no load cairo functions if cairo is disabled
- Cairo is disabled by default
- Avoid crashing when opening a JPEG file fails
- Do not define DYNAMIC_OGL when ANGLE is not enabled
