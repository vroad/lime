package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLRenderbuffer = lime._backend.native.opengl.Renderbuffer;

#else
typedef GLRenderbuffer = js.html.webgl.Renderbuffer;
#end