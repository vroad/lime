package lime.graphics.opengl;

#if (js && html5)
typedef GLES20 = js.html.webgl.RenderingContext;
#else
typedef GLES20 = lime._backend.native.opengl.RenderingContext;
#end