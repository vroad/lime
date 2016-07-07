package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLShaderPrecisionFormat = lime._backend.native.opengl.ShaderPrecisionFormat;

#else
typedef GLShaderPrecisionFormat = js.html.webgl.ShaderPrecisionFormat;
#end