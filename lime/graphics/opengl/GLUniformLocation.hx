package lime.graphics.opengl; #if (!js || !html5 || display)


typedef GLUniformLocation = lime._backend.native.opengl.UniformLocation;


#else
typedef GLUniformLocation = js.html.webgl.UniformLocation;
#end