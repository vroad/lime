package lime.graphics; #if (!js || !html5)


typedef GLRenderContext = lime._backend.native.opengl.RenderingContext;


#else


typedef GLRenderContext = js.html.webgl.RenderingContext;


#end