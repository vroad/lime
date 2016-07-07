package lime.graphics.opengl; #if (!js || !html5 || display)

typedef GLFramebuffer = lime._backend.native.opengl.Framebuffer;

#else
typedef GLFramebuffer = js.html.webgl.Framebuffer;
#end