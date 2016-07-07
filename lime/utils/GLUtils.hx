package lime.utils;


import lime.graphics.GLRenderContext;
import lime.graphics.opengl.GLES20;
import lime.graphics.opengl.GLProgram;
import lime.graphics.opengl.GLShader;


class GLUtils {
	
	
	public static function compileShader (gl:GLRenderContext, source:String, type:Int):GLShader {
		
		var shader = gl.createShader (type);
		gl.shaderSource (shader, source);
		gl.compileShader (shader);
		
		if (gl.getShaderParameter (shader, GLES20.COMPILE_STATUS) == 0) {
			
			var log = gl.getShaderInfoLog (shader);
			
			switch (type) {
				
				case GLES20.VERTEX_SHADER: throw "Error compiling vertex shader\n" + log;
				case GLES20.FRAGMENT_SHADER: throw "Error compiling fragment shader\n" + log;
				default: throw "Error compiling unknown shader type\n" + log;
				
			}
			
		}
		
		return shader;
		
	}
	
	
	public static function createProgram (gl:GLRenderContext, vertexSource:String, fragmentSource:String):GLProgram {
		
		var vertexShader = compileShader (gl, vertexSource, GLES20.VERTEX_SHADER);
		var fragmentShader = compileShader (gl, fragmentSource, GLES20.FRAGMENT_SHADER);
		
		var program = gl.createProgram ();
		gl.attachShader (program, vertexShader);
		gl.attachShader (program, fragmentShader);
		gl.linkProgram (program);
		
		if (gl.getProgramParameter (program, GLES20.LINK_STATUS) == 0) {
			
			throw "Unable to initialize the shader program.";
			
		}
		
		return program;
		
	}
	
	
}