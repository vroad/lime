package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLShader = lime._backend.native.opengl.Shader;

#else
typedef GLShader = js.html.webgl.Shader;
#end