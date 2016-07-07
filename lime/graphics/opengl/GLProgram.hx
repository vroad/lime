package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLProgram = lime._backend.native.opengl.Program;

#else
typedef GLProgram = js.html.webgl.Program;
#end