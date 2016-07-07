package lime.graphics.opengl; #if (!js || !html5)

typedef GLContextAttributes = lime._backend.native.opengl.ContextAttributes;

#else
typedef GLContextAttributes = js.html.webgl.ContextAttributes;
#end