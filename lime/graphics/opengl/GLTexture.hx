package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLTexture = lime._backend.native.opengl.Texture;

#else
typedef GLTexture = js.html.webgl.Texture;
#end