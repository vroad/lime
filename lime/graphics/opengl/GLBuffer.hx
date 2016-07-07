package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLBuffer = lime._backend.native.opengl.Buffer;

#else
typedef GLBuffer = js.html.webgl.Buffer;
#end