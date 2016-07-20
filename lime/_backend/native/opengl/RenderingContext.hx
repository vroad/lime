package lime._backend.native.opengl;

import lime._backend.native.WindowHandle;
import lime._internal.utils.CString;
import lime.system.CFFIPointer;
import lime.utils.ArrayBufferView;
import lime.utils.Float32Array;
import lime.utils.Int32Array;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime._backend.native.opengl.GLObject)
@:access(lime._backend.native.opengl.UniformLocation)


@:cffiInterface("GLContext.xml")
@:cffiCppType("lime::GLContext")
class RenderingContext {
	
	public static inline var DEPTH_BUFFER_BIT : Int = 256;
	public static inline var STENCIL_BUFFER_BIT : Int = 1024;
	public static inline var COLOR_BUFFER_BIT : Int = 16384;
	public static inline var POINTS : Int = 0;
	public static inline var LINES : Int = 1;
	public static inline var LINE_LOOP : Int = 2;
	public static inline var LINE_STRIP : Int = 3;
	public static inline var TRIANGLES : Int = 4;
	public static inline var TRIANGLE_STRIP : Int = 5;
	public static inline var TRIANGLE_FAN : Int = 6;
	public static inline var ZERO : Int = 0;
	public static inline var ONE : Int = 1;
	public static inline var SRC_COLOR : Int = 768;
	public static inline var ONE_MINUS_SRC_COLOR : Int = 769;
	public static inline var SRC_ALPHA : Int = 770;
	public static inline var ONE_MINUS_SRC_ALPHA : Int = 771;
	public static inline var DST_ALPHA : Int = 772;
	public static inline var ONE_MINUS_DST_ALPHA : Int = 773;
	public static inline var DST_COLOR : Int = 774;
	public static inline var ONE_MINUS_DST_COLOR : Int = 775;
	public static inline var SRC_ALPHA_SATURATE : Int = 776;
	public static inline var FUNC_ADD : Int = 32774;
	public static inline var BLEND_EQUATION : Int = 32777;
	public static inline var BLEND_EQUATION_RGB : Int = 32777;
	public static inline var BLEND_EQUATION_ALPHA : Int = 34877;
	public static inline var FUNC_SUBTRACT : Int = 32778;
	public static inline var FUNC_REVERSE_SUBTRACT : Int = 32779;
	public static inline var BLEND_DST_RGB : Int = 32968;
	public static inline var BLEND_SRC_RGB : Int = 32969;
	public static inline var BLEND_DST_ALPHA : Int = 32970;
	public static inline var BLEND_SRC_ALPHA : Int = 32971;
	public static inline var CONSTANT_COLOR : Int = 32769;
	public static inline var ONE_MINUS_CONSTANT_COLOR : Int = 32770;
	public static inline var CONSTANT_ALPHA : Int = 32771;
	public static inline var ONE_MINUS_CONSTANT_ALPHA : Int = 32772;
	public static inline var BLEND_COLOR : Int = 32773;
	public static inline var ARRAY_BUFFER : Int = 34962;
	public static inline var ELEMENT_ARRAY_BUFFER : Int = 34963;
	public static inline var ARRAY_BUFFER_BINDING : Int = 34964;
	public static inline var ELEMENT_ARRAY_BUFFER_BINDING : Int = 34965;
	public static inline var STREAM_DRAW : Int = 35040;
	public static inline var STATIC_DRAW : Int = 35044;
	public static inline var DYNAMIC_DRAW : Int = 35048;
	public static inline var BUFFER_SIZE : Int = 34660;
	public static inline var BUFFER_USAGE : Int = 34661;
	public static inline var CURRENT_VERTEX_ATTRIB : Int = 34342;
	public static inline var FRONT : Int = 1028;
	public static inline var BACK : Int = 1029;
	public static inline var FRONT_AND_BACK : Int = 1032;
	public static inline var CULL_FACE : Int = 2884;
	public static inline var BLEND : Int = 3042;
	public static inline var DITHER : Int = 3024;
	public static inline var STENCIL_TEST : Int = 2960;
	public static inline var DEPTH_TEST : Int = 2929;
	public static inline var SCISSOR_TEST : Int = 3089;
	public static inline var POLYGON_OFFSET_FILL : Int = 32823;
	public static inline var SAMPLE_ALPHA_TO_COVERAGE : Int = 32926;
	public static inline var SAMPLE_COVERAGE : Int = 32928;
	public static inline var NO_ERROR : Int = 0;
	public static inline var INVALID_ENUM : Int = 1280;
	public static inline var INVALID_VALUE : Int = 1281;
	public static inline var INVALID_OPERATION : Int = 1282;
	public static inline var OUT_OF_MEMORY : Int = 1285;
	public static inline var CW : Int = 2304;
	public static inline var CCW : Int = 2305;
	public static inline var LINE_WIDTH : Int = 2849;
	public static inline var ALIASED_POINT_SIZE_RANGE : Int = 33901;
	public static inline var ALIASED_LINE_WIDTH_RANGE : Int = 33902;
	public static inline var CULL_FACE_MODE : Int = 2885;
	public static inline var FRONT_FACE : Int = 2886;
	public static inline var DEPTH_RANGE : Int = 2928;
	public static inline var DEPTH_WRITEMASK : Int = 2930;
	public static inline var DEPTH_CLEAR_VALUE : Int = 2931;
	public static inline var DEPTH_FUNC : Int = 2932;
	public static inline var STENCIL_CLEAR_VALUE : Int = 2961;
	public static inline var STENCIL_FUNC : Int = 2962;
	public static inline var STENCIL_FAIL : Int = 2964;
	public static inline var STENCIL_PASS_DEPTH_FAIL : Int = 2965;
	public static inline var STENCIL_PASS_DEPTH_PASS : Int = 2966;
	public static inline var STENCIL_REF : Int = 2967;
	public static inline var STENCIL_VALUE_MASK : Int = 2963;
	public static inline var STENCIL_WRITEMASK : Int = 2968;
	public static inline var STENCIL_BACK_FUNC : Int = 34816;
	public static inline var STENCIL_BACK_FAIL : Int = 34817;
	public static inline var STENCIL_BACK_PASS_DEPTH_FAIL : Int = 34818;
	public static inline var STENCIL_BACK_PASS_DEPTH_PASS : Int = 34819;
	public static inline var STENCIL_BACK_REF : Int = 36003;
	public static inline var STENCIL_BACK_VALUE_MASK : Int = 36004;
	public static inline var STENCIL_BACK_WRITEMASK : Int = 36005;
	public static inline var VIEWPORT : Int = 2978;
	public static inline var SCISSOR_BOX : Int = 3088;
	public static inline var COLOR_CLEAR_VALUE : Int = 3106;
	public static inline var COLOR_WRITEMASK : Int = 3107;
	public static inline var UNPACK_ALIGNMENT : Int = 3317;
	public static inline var PACK_ALIGNMENT : Int = 3333;
	public static inline var MAX_TEXTURE_SIZE : Int = 3379;
	public static inline var MAX_VIEWPORT_DIMS : Int = 3386;
	public static inline var SUBPIXEL_BITS : Int = 3408;
	public static inline var RED_BITS : Int = 3410;
	public static inline var GREEN_BITS : Int = 3411;
	public static inline var BLUE_BITS : Int = 3412;
	public static inline var ALPHA_BITS : Int = 3413;
	public static inline var DEPTH_BITS : Int = 3414;
	public static inline var STENCIL_BITS : Int = 3415;
	public static inline var POLYGON_OFFSET_UNITS : Int = 10752;
	public static inline var POLYGON_OFFSET_FACTOR : Int = 32824;
	public static inline var TEXTURE_BINDING_2D : Int = 32873;
	public static inline var SAMPLE_BUFFERS : Int = 32936;
	public static inline var SAMPLES : Int = 32937;
	public static inline var SAMPLE_COVERAGE_VALUE : Int = 32938;
	public static inline var SAMPLE_COVERAGE_INVERT : Int = 32939;
	public static inline var COMPRESSED_TEXTURE_FORMATS : Int = 34467;
	public static inline var DONT_CARE : Int = 4352;
	public static inline var FASTEST : Int = 4353;
	public static inline var NICEST : Int = 4354;
	public static inline var GENERATE_MIPMAP_HINT : Int = 33170;
	public static inline var BYTE : Int = 5120;
	public static inline var UNSIGNED_BYTE : Int = 5121;
	public static inline var SHORT : Int = 5122;
	public static inline var UNSIGNED_SHORT : Int = 5123;
	public static inline var INT : Int = 5124;
	public static inline var UNSIGNED_INT : Int = 5125;
	public static inline var FLOAT : Int = 5126;
	public static inline var DEPTH_COMPONENT : Int = 6402;
	public static inline var ALPHA : Int = 6406;
	public static inline var RGB : Int = 6407;
	public static inline var RGBA : Int = 6408;
	public static inline var LUMINANCE : Int = 6409;
	public static inline var LUMINANCE_ALPHA : Int = 6410;
	public static inline var UNSIGNED_SHORT_4_4_4_4 : Int = 32819;
	public static inline var UNSIGNED_SHORT_5_5_5_1 : Int = 32820;
	public static inline var UNSIGNED_SHORT_5_6_5 : Int = 33635;
	public static inline var FRAGMENT_SHADER : Int = 35632;
	public static inline var VERTEX_SHADER : Int = 35633;
	public static inline var MAX_VERTEX_ATTRIBS : Int = 34921;
	public static inline var MAX_VERTEX_UNIFORM_VECTORS : Int = 36347;
	public static inline var MAX_VARYING_VECTORS : Int = 36348;
	public static inline var MAX_COMBINED_TEXTURE_IMAGE_UNITS : Int = 35661;
	public static inline var MAX_VERTEX_TEXTURE_IMAGE_UNITS : Int = 35660;
	public static inline var MAX_TEXTURE_IMAGE_UNITS : Int = 34930;
	public static inline var MAX_FRAGMENT_UNIFORM_VECTORS : Int = 36349;
	public static inline var SHADER_TYPE : Int = 35663;
	public static inline var DELETE_STATUS : Int = 35712;
	public static inline var LINK_STATUS : Int = 35714;
	public static inline var VALIDATE_STATUS : Int = 35715;
	public static inline var ATTACHED_SHADERS : Int = 35717;
	public static inline var ACTIVE_UNIFORMS : Int = 35718;
	public static inline var ACTIVE_ATTRIBUTES : Int = 35721;
	public static inline var SHADING_LANGUAGE_VERSION : Int = 35724;
	public static inline var CURRENT_PROGRAM : Int = 35725;
	public static inline var NEVER : Int = 512;
	public static inline var LESS : Int = 513;
	public static inline var EQUAL : Int = 514;
	public static inline var LEQUAL : Int = 515;
	public static inline var GREATER : Int = 516;
	public static inline var NOTEQUAL : Int = 517;
	public static inline var GEQUAL : Int = 518;
	public static inline var ALWAYS : Int = 519;
	public static inline var KEEP : Int = 7680;
	public static inline var REPLACE : Int = 7681;
	public static inline var INCR : Int = 7682;
	public static inline var DECR : Int = 7683;
	public static inline var INVERT : Int = 5386;
	public static inline var INCR_WRAP : Int = 34055;
	public static inline var DECR_WRAP : Int = 34056;
	public static inline var VENDOR : Int = 7936;
	public static inline var RENDERER : Int = 7937;
	public static inline var VERSION : Int = 7938;
	public static inline var NEAREST : Int = 9728;
	public static inline var LINEAR : Int = 9729;
	public static inline var NEAREST_MIPMAP_NEAREST : Int = 9984;
	public static inline var LINEAR_MIPMAP_NEAREST : Int = 9985;
	public static inline var NEAREST_MIPMAP_LINEAR : Int = 9986;
	public static inline var LINEAR_MIPMAP_LINEAR : Int = 9987;
	public static inline var TEXTURE_MAG_FILTER : Int = 10240;
	public static inline var TEXTURE_MIN_FILTER : Int = 10241;
	public static inline var TEXTURE_WRAP_S : Int = 10242;
	public static inline var TEXTURE_WRAP_T : Int = 10243;
	public static inline var TEXTURE_2D : Int = 3553;
	public static inline var TEXTURE : Int = 5890;
	public static inline var TEXTURE_CUBE_MAP : Int = 34067;
	public static inline var TEXTURE_BINDING_CUBE_MAP : Int = 34068;
	public static inline var TEXTURE_CUBE_MAP_POSITIVE_X : Int = 34069;
	public static inline var TEXTURE_CUBE_MAP_NEGATIVE_X : Int = 34070;
	public static inline var TEXTURE_CUBE_MAP_POSITIVE_Y : Int = 34071;
	public static inline var TEXTURE_CUBE_MAP_NEGATIVE_Y : Int = 34072;
	public static inline var TEXTURE_CUBE_MAP_POSITIVE_Z : Int = 34073;
	public static inline var TEXTURE_CUBE_MAP_NEGATIVE_Z : Int = 34074;
	public static inline var MAX_CUBE_MAP_TEXTURE_SIZE : Int = 34076;
	public static inline var TEXTURE0 : Int = 33984;
	public static inline var TEXTURE1 : Int = 33985;
	public static inline var TEXTURE2 : Int = 33986;
	public static inline var TEXTURE3 : Int = 33987;
	public static inline var TEXTURE4 : Int = 33988;
	public static inline var TEXTURE5 : Int = 33989;
	public static inline var TEXTURE6 : Int = 33990;
	public static inline var TEXTURE7 : Int = 33991;
	public static inline var TEXTURE8 : Int = 33992;
	public static inline var TEXTURE9 : Int = 33993;
	public static inline var TEXTURE10 : Int = 33994;
	public static inline var TEXTURE11 : Int = 33995;
	public static inline var TEXTURE12 : Int = 33996;
	public static inline var TEXTURE13 : Int = 33997;
	public static inline var TEXTURE14 : Int = 33998;
	public static inline var TEXTURE15 : Int = 33999;
	public static inline var TEXTURE16 : Int = 34000;
	public static inline var TEXTURE17 : Int = 34001;
	public static inline var TEXTURE18 : Int = 34002;
	public static inline var TEXTURE19 : Int = 34003;
	public static inline var TEXTURE20 : Int = 34004;
	public static inline var TEXTURE21 : Int = 34005;
	public static inline var TEXTURE22 : Int = 34006;
	public static inline var TEXTURE23 : Int = 34007;
	public static inline var TEXTURE24 : Int = 34008;
	public static inline var TEXTURE25 : Int = 34009;
	public static inline var TEXTURE26 : Int = 34010;
	public static inline var TEXTURE27 : Int = 34011;
	public static inline var TEXTURE28 : Int = 34012;
	public static inline var TEXTURE29 : Int = 34013;
	public static inline var TEXTURE30 : Int = 34014;
	public static inline var TEXTURE31 : Int = 34015;
	public static inline var ACTIVE_TEXTURE : Int = 34016;
	public static inline var REPEAT : Int = 10497;
	public static inline var CLAMP_TO_EDGE : Int = 33071;
	public static inline var MIRRORED_REPEAT : Int = 33648;
	public static inline var FLOAT_VEC2 : Int = 35664;
	public static inline var FLOAT_VEC3 : Int = 35665;
	public static inline var FLOAT_VEC4 : Int = 35666;
	public static inline var INT_VEC2 : Int = 35667;
	public static inline var INT_VEC3 : Int = 35668;
	public static inline var INT_VEC4 : Int = 35669;
	public static inline var BOOL : Int = 35670;
	public static inline var BOOL_VEC2 : Int = 35671;
	public static inline var BOOL_VEC3 : Int = 35672;
	public static inline var BOOL_VEC4 : Int = 35673;
	public static inline var FLOAT_MAT2 : Int = 35674;
	public static inline var FLOAT_MAT3 : Int = 35675;
	public static inline var FLOAT_MAT4 : Int = 35676;
	public static inline var SAMPLER_2D : Int = 35678;
	public static inline var SAMPLER_CUBE : Int = 35680;
	public static inline var VERTEX_ATTRIB_ARRAY_ENABLED : Int = 34338;
	public static inline var VERTEX_ATTRIB_ARRAY_SIZE : Int = 34339;
	public static inline var VERTEX_ATTRIB_ARRAY_STRIDE : Int = 34340;
	public static inline var VERTEX_ATTRIB_ARRAY_TYPE : Int = 34341;
	public static inline var VERTEX_ATTRIB_ARRAY_NORMALIZED : Int = 34922;
	public static inline var VERTEX_ATTRIB_ARRAY_POINTER : Int = 34373;
	public static inline var VERTEX_ATTRIB_ARRAY_BUFFER_BINDING : Int = 34975;
	public static inline var IMPLEMENTATION_COLOR_READ_TYPE : Int = 35738;
	public static inline var IMPLEMENTATION_COLOR_READ_FORMAT : Int = 35739;
	public static inline var COMPILE_STATUS : Int = 35713;
	public static inline var LOW_FLOAT : Int = 36336;
	public static inline var MEDIUM_FLOAT : Int = 36337;
	public static inline var HIGH_FLOAT : Int = 36338;
	public static inline var LOW_INT : Int = 36339;
	public static inline var MEDIUM_INT : Int = 36340;
	public static inline var HIGH_INT : Int = 36341;
	public static inline var FRAMEBUFFER : Int = 36160;
	public static inline var RENDERBUFFER : Int = 36161;
	public static inline var RGBA4 : Int = 32854;
	public static inline var RGB5_A1 : Int = 32855;
	public static inline var RGB565 : Int = 36194;
	public static inline var DEPTH_COMPONENT16 : Int = 33189;
	public static inline var STENCIL_INDEX : Int = 6401;
	public static inline var STENCIL_INDEX8 : Int = 36168;
	public static inline var DEPTH_STENCIL : Int = 34041;
	public static inline var RENDERBUFFER_WIDTH : Int = 36162;
	public static inline var RENDERBUFFER_HEIGHT : Int = 36163;
	public static inline var RENDERBUFFER_INTERNAL_FORMAT : Int = 36164;
	public static inline var RENDERBUFFER_RED_SIZE : Int = 36176;
	public static inline var RENDERBUFFER_GREEN_SIZE : Int = 36177;
	public static inline var RENDERBUFFER_BLUE_SIZE : Int = 36178;
	public static inline var RENDERBUFFER_ALPHA_SIZE : Int = 36179;
	public static inline var RENDERBUFFER_DEPTH_SIZE : Int = 36180;
	public static inline var RENDERBUFFER_STENCIL_SIZE : Int = 36181;
	public static inline var FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE : Int = 36048;
	public static inline var FRAMEBUFFER_ATTACHMENT_OBJECT_NAME : Int = 36049;
	public static inline var FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL : Int = 36050;
	public static inline var FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE : Int = 36051;
	public static inline var COLOR_ATTACHMENT0 : Int = 36064;
	public static inline var DEPTH_ATTACHMENT : Int = 36096;
	public static inline var STENCIL_ATTACHMENT : Int = 36128;
	public static inline var DEPTH_STENCIL_ATTACHMENT : Int = 33306;
	public static inline var NONE : Int = 0;
	public static inline var FRAMEBUFFER_COMPLETE : Int = 36053;
	public static inline var FRAMEBUFFER_INCOMPLETE_ATTACHMENT : Int = 36054;
	public static inline var FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT : Int = 36055;
	public static inline var FRAMEBUFFER_INCOMPLETE_DIMENSIONS : Int = 36057;
	public static inline var FRAMEBUFFER_UNSUPPORTED : Int = 36061;
	public static inline var FRAMEBUFFER_BINDING : Int = 36006;
	public static inline var RENDERBUFFER_BINDING : Int = 36007;
	public static inline var MAX_RENDERBUFFER_SIZE : Int = 34024;
	public static inline var INVALID_FRAMEBUFFER_OPERATION : Int = 1286;
	
	private var extensions:Array<String>;
	
	private function new (handle:ContextHandle) {
		
		this.handle = handle;
		extensions = (getSupportedExtensionsInternal ():String).split (" ");
		
	}
	
	public static function create (window:WindowHandle):RenderingContext {
		
		var handle = createInternal (window);
		return handle != null ? new RenderingContext (handle) : null;
		
	}
	
	public function attachShader (program:Program, shader:Shader):Void {
		
		attachShaderInternal (program != null ? program.handle : null, shader != null ? shader.handle : null);
		
		if (program != null) {
			
			program.attach (shader);
			
		}
		
	}
	
	public function bindAttribLocation (program:Program, index:Int, name:String):Void {
		
		bindAttribLocationInternal (program != null ? program.handle : null, index, name);
		
	}
	
	public function bindBuffer (target:Int, buffer:Buffer):Void {
		
		bindBufferInternal (target, buffer != null ? buffer.handle : null);
		
	}
	
	public function bindFramebuffer (target:Int, framebuffer:Framebuffer):Void {
		
		bindFramebufferInternal (target, framebuffer != null ? framebuffer.handle : null);
		
	}
	
	public function bindRenderbuffer (target:Int, renderbuffer:Renderbuffer):Void {
		
		bindRenderbufferInternal (target, renderbuffer != null ? renderbuffer.handle : null);
		
	}
	
	public function bindTexture (target:Int, texture:Texture):Void {
		
		bindTextureInternal (target, texture != null ? texture.handle : null);
		
	}
	
	public function compileShader (shader:Shader):Void {
		
		compileShaderInternal (shader != null ? shader.handle : null);
		
	}
	
	public function createBuffer ():Buffer {
		
		var handle = createBufferInternal ();
		return handle != null ? new Buffer (handle) : null;
		
	}
	
	public function createFramebuffer ():Framebuffer {
		
		var handle = createFramebufferInternal ();
		return handle != null ? new Framebuffer (handle) : null;
		
	}
	
	public function createProgram ():Program {
		
		var handle = createProgramInternal ();
		return handle != null ? new Program (handle) : null;
		
	}
	
	public function createRenderbuffer ():Renderbuffer {
		
		var handle = createRenderbufferInternal ();
		return handle != null ? new Renderbuffer (handle) : null;
		
	}
	
	public function createShader (type:Int):Shader {
		
		var handle = createShaderInternal (type);
		return handle != null ? new Shader (handle) : null;
		
	}
	
	public function createTexture ():Texture {
		
		var handle = createTextureInternal ();
		return handle != null ? new Texture (handle) : null;
		
	}
	
	public function deleteBuffer (buffer:Buffer):Void {
		
		deleteBufferInternal (buffer != null ? buffer.handle : null);
		
	}
	
	public function deleteFramebuffer (framebuffer:Framebuffer):Void {
		
		deleteFramebufferInternal (framebuffer != null ? framebuffer.handle : null);
		
	}
	
	public function deleteProgram (program:Program):Void {
		
		deleteProgramInternal (program != null ? program.handle : null);
		
	}
	
	public function deleteRenderbuffer (renderbuffer:Renderbuffer):Void {
		
		deleteRenderbufferInternal (renderbuffer != null ? renderbuffer.handle : null);
		
	}
	
	public function deleteShader (shader:Shader):Void {
		
		deleteShaderInternal (shader != null ? shader.handle : null);
		
	}
	
	public function deleteTexture (texture:Texture):Void {
		
		deleteTextureInternal (texture != null ? texture.handle : null);
		
	}
	
	public function detachShader (program:Program, shader:Shader):Void {
		
		detachShaderInternal (program != null ? program.handle : null, shader != null ? shader.handle : null);
		
		if (program != null) {
			
			program.detach (shader);
			
		}
		
	}
	
	public function framebufferRenderbuffer (target:Int, attachment:Int, renderbuffertarget:Int, renderbuffer:Renderbuffer):Void {
		
		framebufferRenderbufferInternal (target, attachment, renderbuffertarget, renderbuffer != null ? renderbuffer.handle : null);
		
	}
	
	public function framebufferTexture2D (target:Int, attachment:Int, textarget:Int, texture:Texture, level:Int):Void {
		
		framebufferTexture2DInternal (target, attachment, textarget, texture != null ? texture.handle : null, level);
		
	}
	
	public function getActiveAttrib (program:Program, index:Int):ActiveInfo {
		
		return getActiveAttribInternal (program != null ? program.handle : null, index);
		
	}
	
	public function getActiveUniform (program:Program, index:Int):ActiveInfo {
		
		return getActiveUniformInternal (program != null ? program.handle : null, index);
		
	}
	
	public function getAttachedShaders (program:Program):Array<Shader> {
		
		return program.getShaders ();
		
	}
	
	public function getAttribLocation (program:Program, name:String):Int {
		
		return getAttribLocationInternal (program != null ? program.handle : null, name);
		
	}
	
	public function getProgramParameter(program:Program, pname:Int):Int {
		
		return getProgramParameterInternal (program != null ? program.handle : null, pname);
		
	}
	
	public function getProgramInfoLog (program:Program):String {
		
		return getProgramInfoLogInternal (program != null ? program.handle : null);
		
	}
	
	public function getShaderInfoLog (shader:Shader):String {
		
		return getShaderInfoLogInternal (shader != null ? shader.handle : null);
		
	}
	
	public function getShaderParameter (shader:Shader, pname:Int):Int {
		
		return getShaderParameterInternal (shader != null ? shader.handle : null, pname);
		
	}
	
	public function getShaderSource (shader:Shader):String {
		
		return getShaderSourceInternal (shader != null ? shader.handle : null);
		
	}
	
	public function getSupportedExtensions ():Array<String> {
		
		return extensions.copy ();
		
	}
	
	public function getUniform (program:Program, location:UniformLocation):Dynamic {
		
		return getUniformInternal (program != null ? program.handle : null, location != null ? location.value : -1);
		
	}
	
	public function getUniformLocation (program:Program, name:String):UniformLocation {
		
		var loc = getUniformLocationInternal (program != null ? program.handle : null, name);
		return loc >= 0 ? new UniformLocation (loc) : null;
		
	}
	
	public function isBuffer (buffer:Buffer):Bool {
		
		return isBufferInternal (buffer != null ? buffer.handle : null);
		
	}
	
	public function isFramebuffer (framebuffer:Framebuffer):Bool {
		
		return isFramebufferInternal (framebuffer != null ? framebuffer.handle : null);
		
	}
	
	public function isProgram (program:Program):Bool {
		
		return isProgramInternal (program != null ? program.handle : null);
		
	}
	
	public function isRenderbuffer (renderbuffer:Renderbuffer):Bool {
		
		return isRenderbufferInternal (renderbuffer != null ? renderbuffer.handle : null);
		
	}
	
	public function isShader (shader:Shader):Bool {
		
		return isShaderInternal (shader != null ? shader.handle : null);
		
	}
	
	public function isTexture (texture:Texture):Bool {
		
		return isTextureInternal (texture != null ? texture.handle : null);
		
	}
	
	public function linkProgram (program:Program):Void {
		
		return linkProgramInternal (program != null ? program.handle : null);
		
	}
	
	public function shaderSource (shader:Shader, source:String):Void {
		
		shaderSourceInternal (shader != null ? shader.handle : null, source);
		
	}
	
	public function uniform1f(location:UniformLocation, x:Float):Void {
		
		uniform1fInternal (location != null ? location.value : -1, x);
		
	}
	
	public function uniform1fv (location:UniformLocation, v : Float32Array ):Void {
		
		uniform1fvInternal (location != null ? location.value : -1, v);
		
	}
	
	public function uniform1i (location:UniformLocation, x : Int ):Void {
		
		uniform1iInternal (location != null ? location.value : -1, x);
		
	}
	
	public function uniform1iv(location:UniformLocation, v : Int32Array ):Void {
	
		uniform1ivInternal (location != null ? location.value : -1, v);
	
	}
	
	public function uniform2f (location:UniformLocation, x : Float, y : Float ):Void {
		
		uniform2fInternal (location != null ? location.value : -1, x, y);
		
	}
	
	public function uniform2fv (location:UniformLocation, v:Float32Array):Void {
		
		uniform2fvInternal (location != null ? location.value : -1, v);
		
	}
	
	public function uniform2i (location:UniformLocation, x:Int, y:Int):Void {
		
		uniform2iInternal (location != null ? location.value : -1, x, y);
		
	}
	
	public function uniform2iv (location:UniformLocation, v : Int32Array ):Void {
	
		uniform2ivInternal (location != null ? location.value : -1, v);
	
	}
	
	public function uniform3f (location:UniformLocation, x : Float, y : Float, z : Float ):Void {
		
		uniform3fInternal (location != null ? location.value : -1, x, y, z);
		
	}
	
	public function uniform3fv (location:UniformLocation, v:Float32Array):Void {
		
		uniform3fvInternal (location != null ? location.value : -1, v);
		
	}
	
	public function uniform3i(location:UniformLocation, x : Int, y : Int, z : Int ):Void {
		
		uniform3iInternal (location != null ? location.value : -1, x, y, z);
		
	}
	
	public function uniform3iv(location:UniformLocation, v : Int32Array ):Void {
	
		uniform3ivInternal (location != null ? location.value : -1, v);
	
	}
	
	public function uniform4f(location:UniformLocation, x : Float, y : Float, z : Float, w : Float ):Void {
		
		uniform4fInternal (location != null ? location.value : -1, x, y, z, w);
		
	}
	
	public function uniform4fv(location:UniformLocation, v:Float32Array):Void {
		
		uniform4fvInternal (location != null ? location.value : -1, v);
		
	}
	
	public function uniform4i(location:UniformLocation, x : Int, y : Int, z : Int, w : Int ):Void {
		
		uniform4iInternal (location != null ? location.value : -1, x, y, z, w);
		
	}
	
	public function uniform4iv(location:UniformLocation, v : Int32Array ):Void {
	
		uniform4ivInternal (location != null ? location.value : -1, v);
	
	}
	
	public function uniformMatrix2fv(location:UniformLocation, transpose : Bool, value : Float32Array ):Void {
		
		uniformMatrix2fvInternal (location != null ? location.value : -1, transpose, value);
		
	}
	
	public function uniformMatrix3fv(location:UniformLocation, transpose : Bool, value : Float32Array ):Void {
		
		uniformMatrix3fvInternal (location != null ? location.value : -1, transpose, value);
		
	}
	
	public function uniformMatrix4fv(location:UniformLocation, transpose : Bool, value : Float32Array ):Void {
		
		uniformMatrix4fvInternal (location != null ? location.value : -1, transpose, value);
		
	}
	
	public function useProgram (program:Program):Void {
		
		useProgramInternal (program != null ? program.handle : null);
		
	}
	
	public function validateProgram (program:Program):Void {
		
		validateProgramInternal (program != null ? program.handle : null);
		
	}
	
	public function vertexAttrib1fv (indx:Int, values:Float32Array):Void {
		
		vertexAttrib1fvInternal (indx, values);
		
	}
	
	public function vertexAttrib2fv (indx:Int, values:Float32Array):Void {
		
		vertexAttrib2fvInternal (indx, values);
		
	}
	
	public function vertexAttrib3fv (indx:Int, values:Float32Array):Void {
		
		vertexAttrib3fvInternal (indx, values);
		
	}
	
	public function vertexAttrib4fv (indx:Int, values:Float32Array):Void {
		
		vertexAttrib4fvInternal (indx, values);
		
	}
	
	@:cffi @:cffiFreeAbstract public function dispose ():Void { throw null; }
	
	@:cffi public function getContextAttributes() : ContextAttributes { throw null; }
	@:cffi public function isContextLost() : Bool { throw null; }
	@:cffi public function getSupportedExtensionsInternal() : Dynamic { throw null; }
	@:cffi public function getExtension( name : CString ) : Dynamic { throw null; }
	@:cffi public function activeTexture( texture : Int ) : Void { throw null; }
	@:cffi private function attachShaderInternal( program : ProgramHandle, shader : ShaderHandle ) : Void { throw null; }
	@:cffi private function bindAttribLocationInternal( program : ProgramHandle, index : Int, name : CString ) : Void { throw null; }
	@:cffi private function bindBufferInternal( target : Int, buffer : BufferHandle ) : Void { throw null; }
	@:cffi private function bindFramebufferInternal( target : Int, framebuffer : FramebufferHandle ) : Void { throw null; }
	@:cffi private function bindRenderbufferInternal( target : Int, renderbuffer : RenderbufferHandle ) : Void { throw null; }
	@:cffi private function bindTextureInternal( target : Int, texture : TextureHandle ) : Void { throw null; }
	@:cffi public function blendColor( red : Float, green : Float, blue : Float, alpha : Float ) : Void { throw null; }
	@:cffi public function blendEquation( mode : Int ) : Void { throw null; }
	@:cffi public function blendEquationSeparate( modeRGB : Int, modeAlpha : Int ) : Void { throw null; }
	@:cffi public function blendFunc( sfactor : Int, dfactor : Int ) : Void { throw null; }
	@:cffi public function blendFuncSeparate( srcRGB : Int, dstRGB : Int, srcAlpha : Int, dstAlpha : Int ) : Void { throw null; }
	@:cffi public function bufferData( target : Int, data : ArrayBufferView, usage : Int ) : Void { throw null; }
	@:cffi public function bufferSubData( target : Int, offset : Int, data : ArrayBufferView ) : Void { throw null; }
	@:cffi public function checkFramebufferStatus( target : Int ) : Int { throw null; }
	@:cffi public function clear( mask : Int ) : Void { throw null; }
	@:cffi public function clearColor( red : Float, green : Float, blue : Float, alpha : Float ) : Void { throw null; }
	@:cffi public function clearDepth( depth : Float ) : Void { throw null; }
	@:cffi public function clearStencil( s : Int ) : Void { throw null; }
	@:cffi public function colorMask( red : Bool, green : Bool, blue : Bool, alpha : Bool ) : Void { throw null; }
	@:cffi private function compileShaderInternal( shader : ShaderHandle ) : Void { throw null; }
	@:cffi public function compressedTexImage2D( target : Int, level : Int, internalformat : Int, width : Int, height : Int, border : Int, data : ArrayBufferView ) : Void { throw null; }
	@:cffi public function compressedTexSubImage2D( target : Int, level : Int, xoffset : Int, yoffset : Int, width : Int, height : Int, format : Int, data : ArrayBufferView ) : Void { throw null; }
	@:cffi public function copyTexImage2D( target : Int, level : Int, internalformat : Int, x : Int, y : Int, width : Int, height : Int, border : Int ) : Void { throw null; }
	@:cffi public function copyTexSubImage2D( target : Int, level : Int, xoffset : Int, yoffset : Int, x : Int, y : Int, width : Int, height : Int ) : Void { throw null; }
	@:cffi private static function createInternal(window:CFFIPointer):ContextHandle { throw null; }
	@:cffi private function createBufferInternal() : BufferHandle { throw null; }
	@:cffi private function createFramebufferInternal() : FramebufferHandle { throw null; }
	@:cffi private function createProgramInternal() : ProgramHandle { throw null; }
	@:cffi private function createRenderbufferInternal() : RenderbufferHandle { throw null; }
	@:cffi private function createShaderInternal( type : Int ) : ShaderHandle { throw null; }
	@:cffi private function createTextureInternal() : TextureHandle { throw null; }
	@:cffi public function cullFace( mode : Int ) : Void { throw null; }
	@:cffi private function deleteBufferInternal( buffer : CFFIPointer ) : Void { throw null; }
	@:cffi private function deleteFramebufferInternal( framebuffer : CFFIPointer ) : Void { throw null; }
	@:cffi private function deleteProgramInternal( program : CFFIPointer ) : Void { throw null; }
	@:cffi private function deleteRenderbufferInternal( renderbuffer : CFFIPointer ) : Void { throw null; }
	@:cffi private function deleteShaderInternal( shader : CFFIPointer ) : Void { throw null; }
	@:cffi private function deleteTextureInternal( texture : CFFIPointer ) : Void { throw null; }
	@:cffi public function depthFunc( func : Int ) : Void { throw null; }
	@:cffi public function depthMask( flag : Bool ) : Void { throw null; }
	@:cffi public function depthRange( zNear : Float, zFar : Float ) : Void { throw null; }
	@:cffi public function detachShaderInternal( program : ProgramHandle, shader : ShaderHandle ) : Void { throw null; }
	@:cffi public function disable( cap : Int ) : Void { throw null; }
	@:cffi public function disableVertexAttribArray( index : Int ) : Void { throw null; }
	@:cffi public function drawArrays( mode : Int, first : Int, count : Int ) : Void { throw null; }
	@:cffi public function drawElements( mode : Int, count : Int, type : Int, offset : Int ) : Void { throw null; }
	@:cffi public function enable( cap : Int ) : Void { throw null; }
	@:cffi public function enableVertexAttribArray( index : Int ) : Void { throw null; }
	@:cffi public function finish() : Void { throw null; }
	@:cffi public function flush() : Void { throw null; }
	@:cffi private function framebufferRenderbufferInternal( target : Int, attachment : Int, renderbuffertarget : Int, renderbuffer : RenderbufferHandle ) : Void { throw null; }
	@:cffi private function framebufferTexture2DInternal( target : Int, attachment : Int, textarget : Int, texture : TextureHandle, level : Int ) : Void { throw null; }
	@:cffi public function frontFace( mode : Int ) : Void { throw null; }
	@:cffi public function generateMipmap( target : Int ) : Void { throw null; }
	@:cffi private function getActiveAttribInternal( program : ProgramHandle, index : Int ) : ActiveInfo { throw null; }
	@:cffi private function getActiveUniformInternal( program : ProgramHandle, index : Int ) : ActiveInfo { throw null; }
	@:cffi private function getAttribLocationInternal( program : ProgramHandle, name : CString ) : Int { throw null; }
	@:cffi public function getBufferParameter( target : Int, pname : Int ) : Int { throw null; }
	@:cffi public function getParameter( pname : Int ) : Dynamic { throw null; }
	@:cffi public function getError() : Int { throw null; }
	@:cffi public function getFramebufferAttachmentParameter( target : Int, attachment : Int, pname : Int ) : Int { throw null; }
	@:cffi private function getProgramParameterInternal( program : ProgramHandle, pname : Int ) : Int { throw null; }
	@:cffi private function getProgramInfoLogInternal( program : ProgramHandle ) : Dynamic { throw null; }
	@:cffi public function getRenderbufferParameter( target : Int, pname : Int ) : Int { throw null; }
	@:cffi private function getShaderParameterInternal( shader : ShaderHandle, pname : Int ) : Int { throw null; }
	@:cffi public function getShaderPrecisionFormat( shadertype : Int, precisiontype : Int ) : ShaderPrecisionFormat { throw null; }
	@:cffi private function getShaderInfoLogInternal( shader : ShaderHandle ) : Dynamic { throw null; }
	@:cffi private function getShaderSourceInternal( shader : ShaderHandle ) : Dynamic { throw null; }
	@:cffi public function getTexParameter( target : Int, pname : Int ) : Int { throw null; }
	@:cffi private function getUniformInternal( program : ProgramHandle, location : Int ) : Dynamic { throw null; }
	@:cffi private function getUniformLocationInternal( program : ProgramHandle, name : CString ) : Int { throw null; }
	@:cffi public function getVertexAttrib( index : Int, pname : Int ) : Int { throw null; }
	@:cffi public function getVertexAttribOffset( index : Int, pname : Int ) : Int { throw null; }
	@:cffi public function hint( target : Int, mode : Int ) : Void { throw null; }
	@:cffi private function isBufferInternal( buffer : BufferHandle ) : Bool { throw null; }
	@:cffi public function isEnabled( cap : Int ) : Bool { throw null; }
	@:cffi private function isFramebufferInternal( framebuffer : FramebufferHandle ) : Bool { throw null; }
	@:cffi private function isProgramInternal( program : ProgramHandle ) : Bool { throw null; }
	@:cffi private function isRenderbufferInternal( renderbuffer : RenderbufferHandle ) : Bool { throw null; }
	@:cffi private function isShaderInternal( shader : ShaderHandle ) : Bool { throw null; }
	@:cffi private function isTextureInternal( texture : TextureHandle ) : Bool { throw null; }
	@:cffi public function lineWidth( width : Float ) : Void { throw null; }
	@:cffi private function linkProgramInternal( program : ProgramHandle ) : Void { throw null; }
	@:cffi public function pixelStorei( pname : Int, param : Int ) : Void { throw null; }
	@:cffi public function polygonOffset( factor : Float, units : Float ) : Void { throw null; }
	@:cffi public function readPixels( x : Int, y : Int, width : Int, height : Int, format : Int, type : Int, pixels : ArrayBufferView ) : Void { throw null; }
	@:cffi public function renderbufferStorage( target : Int, internalformat : Int, width : Int, height : Int ) : Void { throw null; }
	@:cffi public function sampleCoverage( value : Float, invert : Bool ) : Void { throw null; }
	@:cffi public function scissor( x : Int, y : Int, width : Int, height : Int ) : Void { throw null; }
	@:cffi private function shaderSourceInternal( shader : ShaderHandle, source : String ) : Void { throw null; }
	@:cffi public function stencilFunc( func : Int, ref : Int, mask : Int ) : Void { throw null; }
	@:cffi public function stencilFuncSeparate( face : Int, func : Int, ref : Int, mask : Int ) : Void { throw null; }
	@:cffi public function stencilMask( mask : Int ) : Void { throw null; }
	@:cffi public function stencilMaskSeparate( face : Int, mask : Int ) : Void { throw null; }
	@:cffi public function stencilOp( fail : Int, zfail : Int, zpass : Int ) : Void { throw null; }
	@:cffi public function stencilOpSeparate( face : Int, fail : Int, zfail : Int, zpass : Int ) : Void { throw null; }
	@:cffi public function texImage2D( target : Int, level : Int, internalformat : Int, width : Int, height : Int, border : Int, format : Int, type : Int, pixels : ArrayBufferView ) : Void { throw null; }
	@:cffi public function texParameterf( target : Int, pname : Int, param : Float ) : Void { throw null; }
	@:cffi public function texParameteri( target : Int, pname : Int, param : Int ) : Void { throw null; }
	@:cffi public function texSubImage2D( target : Int, level : Int, xoffset : Int, yoffset : Int, width : Int, height : Int, format : Int, type : Int, pixels : ArrayBufferView ) : Void { throw null; }
	@:cffi private function uniform1fInternal( location : Int, x : Float ) : Void { throw null; }
	@:cffi private function uniform1fvInternal( location : Int, v : Float32Array) : Void { throw null; }
	@:cffi private function uniform1iInternal( location : Int, x : Int ) : Void { throw null; }
	@:cffi private function uniform1ivInternal( location : Int, v : Int32Array) : Void { throw null; }
	@:cffi private function uniform2fInternal( location : Int, x : Float, y : Float ) : Void { throw null; }
	@:cffi private function uniform2fvInternal( location : Int, v : Float32Array) : Void { throw null; }
	@:cffi private function uniform2iInternal( location : Int, x : Int, y : Int ) : Void { throw null; }
	@:cffi private function uniform2ivInternal( location : Int, v : Int32Array) : Void { throw null; }
	@:cffi private function uniform3fInternal( location : Int, x : Float, y : Float, z : Float ) : Void { throw null; }
	@:cffi private function uniform3fvInternal( location : Int, v : Float32Array) : Void { throw null; }
	@:cffi private function uniform3iInternal( location : Int, x : Int, y : Int, z : Int ) : Void { throw null; }
	@:cffi private function uniform3ivInternal( location : Int, v : Int32Array) : Void { throw null; }
	@:cffi private function uniform4fInternal( location : Int, x : Float, y : Float, z : Float, w : Float ) : Void { throw null; }
	@:cffi private function uniform4fvInternal( location : Int, v : Float32Array) : Void { throw null; }
	@:cffi private function uniform4iInternal( location : Int, x : Int, y : Int, z : Int, w : Int ) : Void { throw null; }
	@:cffi private function uniform4ivInternal( location : Int, v : Int32Array) : Void { throw null; }
	@:cffi private function uniformMatrix2fvInternal( location : Int, transpose : Bool, value : Float32Array) : Void { throw null; }
	@:cffi private function uniformMatrix3fvInternal( location : Int, transpose : Bool, value : Float32Array) : Void { throw null; }
	@:cffi private function uniformMatrix4fvInternal( location : Int, transpose : Bool, value : Float32Array) : Void { throw null; }
	@:cffi private function useProgramInternal( program : ProgramHandle ) : Void { throw null; }
	@:cffi private function validateProgramInternal( program : ProgramHandle ) : Void { throw null; }
	@:cffi public function vertexAttrib1f( indx : Int, x : Float ) : Void { throw null; }
	@:cffi public function vertexAttrib1fvInternal( indx : Int, values : Float32Array) : Void { throw null; }
	@:cffi public function vertexAttrib2f( indx : Int, x : Float, y : Float ) : Void { throw null; }
	@:cffi public function vertexAttrib2fvInternal( indx : Int, values : Float32Array) : Void { throw null; }
	@:cffi public function vertexAttrib3f( indx : Int, x : Float, y : Float, z : Float ) : Void { throw null; }
	@:cffi public function vertexAttrib3fvInternal( indx : Int, values : Float32Array) : Void { throw null; }
	@:cffi public function vertexAttrib4f( indx : Int, x : Float, y : Float, z : Float, w : Float ) : Void { throw null; }
	@:cffi public function vertexAttrib4fvInternal( indx : Int, values : Float32Array) : Void { throw null; }
	@:cffi public function vertexAttribPointer( indx : Int, size : Int, type : Int, normalized : Bool, stride : Int, offset : Int ) : Void { throw null; }
	@:cffi public function viewport( x : Int, y : Int, width : Int, height : Int ) : Void { throw null; }
	
	@:cffiHandle public var handle(default, null):ContextHandle;
	
}