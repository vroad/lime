#include <graphics/opengl/GLContext.h>
#include <hx/CFFIPrime.h>
#include <system/CFFIPointer.h>
#include <utils/Bytes.h>
#include <graphics/opengl/OpenGL.h>
#include <graphics/opengl/OpenGLBindings.h>

#ifdef NEED_EXTENSIONS
#define DEFINE_EXTENSION
#include <graphics/opengl/OpenGLExtensions.h>
#undef DEFINE_EXTENSION
#endif

#include <SDL.h>

#include <utils/ArrayBufferView.h>
#include <utils/PointerUtils.h>
#include <utils/Kinds.h>

#include <assert.h>

namespace lime {
	
	GLContext::GLContext () {
		
		weakRefCount = 1;
		
	}
	
	GLContext::~GLContext () {
		
		ClearDeletionQueue ();
		
	}
	
	bool GLContext::Init (value inWindow) {
		
		if (!OpenGLBindings::Init ()) {
			
			return false;
			
		}
		
		context.reset (GLContextHandle::Create (inWindow));
		
		if (!context) {
			
			return false;
			
		}
		
		return true;
		
	}
	
	void GLContext::dispose () {
		
		context.reset (NULL);
		ClearDeletionQueue ();
		ReleaseWeakRef ();
		
	}
	
	bool GLContext::IsDisposed () {
		
		return !context;
		
	}
	
	void GLContext::AddWeakRef () {
		
		weakRefCount++;
		
	}
	
	bool GLContext::ReleaseWeakRef () {
		
		assert (weakRefCount >= 1);
		weakRefCount--;
		
		if (weakRefCount == 0) {
			
			delete this;
			return true;
			
		}
		
		return false;
		
	}
	
	void GLContext::AddGLObjectToDeletionQueue (GLObject* obj, GLResourceType type) {
		
		assert (context);
		deletionQueue.push_back (GLResource (obj, type));
		
	}
	
	value GLContext::getContextAttributes () {
		
		// TODO
		value result = alloc_empty_object ();
		
		alloc_field (result, val_id ("alpha"), alloc_bool (true));
		alloc_field (result, val_id ("depth"), alloc_bool (true));
		alloc_field (result, val_id ("stencil"), alloc_bool (true));
		alloc_field (result, val_id ("antialias"), alloc_bool (true));
		
		return result;
		
	}
	
	bool GLContext::isContextLost () {
		
		// TODO
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return false;
		
	}
	
	value GLContext::getSupportedExtensionsInternal () {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		const char* extensions = (const char*)glGetString (GL_EXTENSIONS);
		return alloc_string (extensions);
		
	}
	
	value GLContext::getExtension (const char* name) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		
		void *result = NULL;
		
		#ifdef LIME_SDL
		result = SDL_GL_GetProcAddress (name);
		#endif
		
		return alloc_bool (result != NULL);
		
	}
	
	void GLContext::activeTexture (int texture) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glActiveTexture (texture);
		
	}
	
	void GLContext::attachShaderInternal (GLProgram* program, GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glAttachShader (program ? program->id : 0, shader ? shader->id : 0);
		
	}
	
	void GLContext::bindAttribLocationInternal (GLProgram* program, int index, const char* name) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBindAttribLocation (program ? program->id : 0, index, name);
		
	}
	
	void GLContext::bindBufferInternal (int target, GLBuffer* buffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBindBuffer (target, buffer ? buffer->id : 0);
		
	}
	
	void GLContext::bindFramebufferInternal (int target, GLFramebuffer* framebuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBindFramebuffer (target, framebuffer ? framebuffer->id : 0);
		
	}
	
	void GLContext::bindRenderbufferInternal (int target, GLRenderbuffer* renderbuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBindRenderbuffer (target, renderbuffer ? renderbuffer->id : 0);
		
	}
	
	void GLContext::bindTextureInternal (int target, GLTexture* texture) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBindTexture (target, texture ? texture->id : 0);
		
	}
	
	void GLContext::blendColor (double red, double green, double blue, double alpha) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBlendColor (red, green, blue, alpha);
		
	}
	
	void GLContext::blendEquation (int mode) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBlendEquation (mode);
		
	}
	
	void GLContext::blendEquationSeparate (int modeRGB, int modeAlpha) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBlendEquationSeparate (modeRGB, modeAlpha);
		
	}
	
	void GLContext::blendFunc (int sfactor, int dfactor) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBlendFunc (sfactor, dfactor);
		
	}
	
	void GLContext::blendFuncSeparate (int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBlendFuncSeparate (srcRGB, dstRGB, srcAlpha, dstAlpha);
		
	}
	
	void GLContext::bufferDataInternal (int target, ArrayBufferView* data, int usage) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBufferData (target, data ? data->ByteLength () : 0, data ? data->Data () : NULL, usage);
		
	}
	
	void GLContext::bufferSubDataInternal (int target, int offset, ArrayBufferView* data) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glBufferSubData (target, offset, data->ByteLength (), data ? data->Data () : NULL);
		
	}
	
	int GLContext::checkFramebufferStatus (int target) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		return glCheckFramebufferStatus (target);
		
	}
	
	void GLContext::clear (int mask) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glClear (mask);
		
	}
	
	void GLContext::clearColor (double red, double green, double blue, double alpha) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glClearColor (red, green, blue, alpha);
		
	}
	
	void GLContext::clearDepth (double depth) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		#ifdef LIME_GLES
		glClearDepthf (depth);
		#else
		glClearDepth (depth);
		#endif
		
	}
	
	void GLContext::clearStencil (int s) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glClearStencil (s);
		
	}
	
	void GLContext::colorMask (bool red, bool green, bool blue, bool alpha) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glColorMask (red, green, blue, alpha);
		
	}
	
	void GLContext::compileShaderInternal (GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCompileShader (shader ? shader->id : 0);
		
	}
	
	void GLContext::compressedTexImage2DInternal (int target, int level, int internalformat, int width, int height, int border, ArrayBufferView* data) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCompressedTexImage2D (target, level, internalformat, width, height, border, data ? data->ByteLength () : 0, data ? data->Data () : NULL);
		
	}
	
	void GLContext::compressedTexSubImage2DInternal (int target, int level, int xoffset, int yoffset, int width, int height, int format, ArrayBufferView* data) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCompressedTexSubImage2D (target, level, xoffset, yoffset, width, height, format, data ? data->ByteLength () : 0, data ? data->Data () : NULL);
		
	}
	
	void GLContext::copyTexImage2D (int target, int level, int internalformat, int x, int y, int width, int height, int border) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCopyTexImage2D (target, level, internalformat, x, y, width, height, border);
		
	}
	
	void GLContext::copyTexSubImage2D (int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCopyTexSubImage2D (target, level, xoffset, yoffset, x, y, width, height);
		
	}
	
	GLContext* GLContext::createInternal (value inWindow) {
		
		GLContext *context = new GLContext ();
		
		if (!context->Init (inWindow)) {
			
			delete context;
			return NULL;
			
		}
		
		return context;
		
	}
	
	GLBuffer* GLContext::createBufferInternal () {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		GLuint buffer;
		glGenBuffers (1, &buffer);
		return new GLBuffer (this, buffer);
		
	}
	
	GLFramebuffer* GLContext::createFramebufferInternal () {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		GLuint id;
		glGenFramebuffers (1, &id);
		return new GLFramebuffer (this, id);
		
	}
	
	GLProgram* GLContext::createProgramInternal () {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		return new GLProgram (this, glCreateProgram ());
		
	}
	
	GLRenderbuffer* GLContext::createRenderbufferInternal () {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		GLuint id = 0;
		glGenRenderbuffers (1, &id);
		return new GLRenderbuffer (this, id);
		
	}
	
	GLShader* GLContext::createShaderInternal (int type) {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		return new GLShader (this, glCreateShader (type));
		
	}
	
	GLTexture* GLContext::createTextureInternal () {
		
		if (!checkStatus ()) {
			
			return NULL;
			
		}
		
		unsigned int id;
		glGenTextures (1, &id);
		return new GLTexture (this, id);
		
	}
	
	void GLContext::cullFace (int mode) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glCullFace (mode);
		
	}
	
	void GLContext::deleteBufferInternal (value inBuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLBuffer* buffer = val_to_GLBuffer (inBuffer);
		GLuint id = buffer ? buffer->id : 0;
		glDeleteBuffers (1, &id);
		delete buffer;
		free_abstract (inBuffer);
		
	}
	
	void GLContext::deleteFramebufferInternal (value inFramebuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLFramebuffer* framebuffer = val_to_GLFramebuffer (inFramebuffer);
		GLuint id = framebuffer ? framebuffer->id : 0;
		glDeleteFramebuffers (1, &id);
		delete framebuffer;
		free_abstract (inFramebuffer);
		
	}
	
	void GLContext::deleteProgramInternal (value inProgram) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLProgram* program = val_to_GLProgram (inProgram);
		glDeleteProgram (program ? program->id : 0);
		delete program;
		free_abstract (inProgram);
		
	}
	
	void GLContext::deleteRenderbufferInternal (value inRenderbuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLRenderbuffer* renderbuffer = val_to_GLRenderbuffer (inRenderbuffer);
		GLuint id = renderbuffer ? renderbuffer->id : 0;
		glDeleteRenderbuffers (1, &id);
		delete renderbuffer;
		free_abstract (inRenderbuffer);
		
	}
	
	void GLContext::deleteShaderInternal (value inShader) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLShader* shader = val_to_GLShader (inShader);
		glDeleteShader (shader ? shader->id : 0);
		delete shader;
		free_abstract (inShader);
		
	}
	
	void GLContext::deleteTextureInternal (value inTexture) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		GLTexture* texture = val_to_GLTexture (inTexture);
		GLuint id = texture ? texture->id : 0;
		glDeleteTextures (1, &id);
		delete texture;
		free_abstract (inTexture);
		
	}
	
	void GLContext::depthFunc (int func) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDepthFunc (func);
		
	}
	
	void GLContext::depthMask (bool flag) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDepthMask (flag);
		
	}
	
	void GLContext::depthRange (double zNear, double zFar) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		#ifdef LIME_GLES
		glDepthRangef (zNear, zFar);
		#else
		glDepthRange (zNear, zFar);
		#endif
		
	}
	
	void GLContext::detachShaderInternal (GLProgram* program, GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDetachShader (program ? program->id : 0, shader ? shader->id : 0);
		
	}
	
	void GLContext::disable (int cap) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDisable (cap);
		
	}
	
	void GLContext::disableVertexAttribArray (int index) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDisableVertexAttribArray (index);
		
	}
	
	void GLContext::drawArrays (int mode, int first, int count) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDrawArrays (mode, first, count);
		
	}
	
	void GLContext::drawElements (int mode, int count, int type, int offset) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glDrawElements (mode, count, type, (void*)(intptr_t)offset);
		
	}
	
	void GLContext::enable (int cap) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glEnable (cap);
	}
	
	void GLContext::enableVertexAttribArray (int index) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glEnableVertexAttribArray (index);
	}
	
	void GLContext::finish () {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glFinish ();
		
	}
	
	void GLContext::flush () {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glFlush ();
		
	}
	
	void GLContext::framebufferRenderbufferInternal (int target, int attachment, int renderbuffertarget, GLRenderbuffer* renderbuffer) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glFramebufferRenderbuffer (target, attachment, renderbuffertarget, renderbuffer ? renderbuffer->id : 0);
		
	}
	
	void GLContext::framebufferTexture2DInternal (int target, int attachment, int textarget, GLTexture* texture, int level) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glFramebufferTexture2D (target, attachment, textarget, texture ? texture->id : 0, level);
		
	}
	
	void GLContext::frontFace (int mode) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glFrontFace (mode);
	}
	
	void GLContext::generateMipmap (int target) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glGenerateMipmap (target);
		
	}
	
	value GLContext::getActiveAttribInternal (GLProgram* program, int index) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		GLuint programId = program ? program->id : 0;
		GLint bufSize;
		glGetProgramiv (programId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &bufSize);
		
		if (bufSize == 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<GLchar> buf (bufSize);
		GLsizei size = 0;
		GLenum  type = 0;
		GLsizei outLen;
		
		glGetActiveAttrib (programId, index, bufSize, &outLen, &size, &type, &buf[0]);
		
		value result = alloc_empty_object ();
		alloc_field (result, val_id ("size"), alloc_int (size));
		alloc_field (result, val_id ("type"), alloc_int (type));
		alloc_field (result, val_id ("name"), alloc_string_len (&buf[0], outLen));
		
		return result;
		
	}
	
	value GLContext::getActiveUniformInternal (GLProgram* program, int index) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		GLuint programId = program ? program->id : 0;
		GLint bufSize;
		glGetProgramiv (programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &bufSize);
		
		if (bufSize == 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<GLchar> buf (bufSize);
		GLsizei size = 0;
		GLenum  type = 0;
		GLsizei outLen;
		
		glGetActiveUniform (programId, index, bufSize, &outLen, &size, &type, &buf[0]);
		
		value result = alloc_empty_object ();
		alloc_field (result, val_id ("size"), alloc_int (size));
		alloc_field (result, val_id ("type"), alloc_int (type));
		alloc_field (result, val_id ("name"), alloc_string_len (&buf[0], outLen));
		
		return result;
		
	}
	
	int GLContext::getAttribLocationInternal (GLProgram* program, const char* name) {
		
		if (!checkStatus ()) {
			
			return -1;
			
		}
		
		return glGetAttribLocation (program ? program->id : 0, name);
		
	}
	
	int GLContext::getBufferParameter (int target, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint data;
		glGetBufferParameteriv (target, pname, &data);
		return data;
		
	}
	
	value GLContext::getParameter (int pname) {
		
		int floats = 0;
		int ints = 0;
		int strings = 0;
		
		switch (pname) {
			
			case GL_ALIASED_LINE_WIDTH_RANGE:
			case GL_ALIASED_POINT_SIZE_RANGE:
			case GL_DEPTH_RANGE:
				floats = 2;
				break;
			
			case GL_BLEND_COLOR:
			case GL_COLOR_CLEAR_VALUE:
				floats = 4;
				break;
			
			case GL_COLOR_WRITEMASK:
				ints = 4;
				break;
			
			//case GL_COMPRESSED_TEXTURE_FORMATS  null
			
			case GL_MAX_VIEWPORT_DIMS:
				ints = 2;
				break;
			
			case GL_SCISSOR_BOX:
			case GL_VIEWPORT:
				ints = 4;
				break;
			
			case GL_ARRAY_BUFFER_BINDING:
			case GL_CURRENT_PROGRAM:
			case GL_ELEMENT_ARRAY_BUFFER_BINDING:
			case GL_FRAMEBUFFER_BINDING:
			case GL_RENDERBUFFER_BINDING:
			case GL_TEXTURE_BINDING_2D:
			case GL_TEXTURE_BINDING_CUBE_MAP:
			case GL_DEPTH_CLEAR_VALUE:
			case GL_LINE_WIDTH:
			case GL_POLYGON_OFFSET_FACTOR:
			case GL_POLYGON_OFFSET_UNITS:
			case GL_SAMPLE_COVERAGE_VALUE:
				ints = 1;
				break;
			
			case GL_BLEND:
			case GL_DEPTH_WRITEMASK:
			case GL_DITHER:
			case GL_CULL_FACE:
			case GL_POLYGON_OFFSET_FILL:
			case GL_SAMPLE_COVERAGE_INVERT:
			case GL_STENCIL_TEST:
			//case GL_UNPACK_FLIP_Y_WEBGL:
			//case GL_UNPACK_PREMULTIPLY_ALPHA_WEBGL:
				ints = 1;
				break;
			
			case GL_ALPHA_BITS:
			case GL_ACTIVE_TEXTURE:
			case GL_BLEND_DST_ALPHA:
			case GL_BLEND_DST_RGB:
			case GL_BLEND_EQUATION_ALPHA:
			case GL_BLEND_EQUATION_RGB:
			case GL_BLEND_SRC_ALPHA:
			case GL_BLEND_SRC_RGB:
			case GL_BLUE_BITS:
			case GL_CULL_FACE_MODE:
			case GL_DEPTH_BITS:
			case GL_DEPTH_FUNC:
			case GL_DEPTH_TEST:
			case GL_FRONT_FACE:
			case GL_GENERATE_MIPMAP_HINT:
			case GL_GREEN_BITS:
			case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS:
			case GL_MAX_CUBE_MAP_TEXTURE_SIZE:
			//case GL_MAX_FRAGMENT_UNIFORM_VECTORS:
			//case GL_MAX_RENDERBUFFER_SIZE:
			case GL_MAX_TEXTURE_IMAGE_UNITS:
			case GL_MAX_TEXTURE_SIZE:
			//case GL_MAX_VARYING_VECTORS:
			case GL_MAX_VERTEX_ATTRIBS:
			case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS:
			case GL_MAX_VERTEX_UNIFORM_VECTORS:
			case GL_NUM_COMPRESSED_TEXTURE_FORMATS:
			case GL_PACK_ALIGNMENT:
			case GL_RED_BITS:
			case GL_SAMPLE_BUFFERS:
			case GL_SAMPLES:
			case GL_SCISSOR_TEST:
			case GL_SHADING_LANGUAGE_VERSION:
			case GL_STENCIL_BACK_FAIL:
			case GL_STENCIL_BACK_FUNC:
			case GL_STENCIL_BACK_PASS_DEPTH_FAIL:
			case GL_STENCIL_BACK_PASS_DEPTH_PASS:
			case GL_STENCIL_BACK_REF:
			case GL_STENCIL_BACK_VALUE_MASK:
			case GL_STENCIL_BACK_WRITEMASK:
			case GL_STENCIL_BITS:
			case GL_STENCIL_CLEAR_VALUE:
			case GL_STENCIL_FAIL:
			case GL_STENCIL_FUNC:
			case GL_STENCIL_PASS_DEPTH_FAIL:
			case GL_STENCIL_PASS_DEPTH_PASS:
			case GL_STENCIL_REF:
			case GL_STENCIL_VALUE_MASK:
			case GL_STENCIL_WRITEMASK:
			case GL_SUBPIXEL_BITS:
			case GL_UNPACK_ALIGNMENT:
			//case GL_UNPACK_COLORSPACE_CONVERSION_WEBGL:
				ints = 1;
				break;
			
			case GL_VENDOR:
			case GL_VERSION:
			case GL_RENDERER:
				strings = 1;
				break;
			
		}
		
		if (ints == 1) {
			
			int val;
			glGetIntegerv (pname, &val);
			return alloc_int (val);
			
		} else if (strings == 1) {
			
			return alloc_string ((const char *)glGetString (pname));
			
		} else if (floats == 1) {
			
			float f;
			glGetFloatv (pname, &f);
			return alloc_float (f);
			
		} else if (ints > 0) {
			
			int vals[4];
			glGetIntegerv (pname, vals);
			value result = alloc_array (ints);
			
			for (int i = 0; i < ints; i++) {
				
				val_array_set_i (result, i, alloc_int (vals[i]));
				
			}
			
			return result;
			
		} else if (floats > 0) {
			
			float vals[4];
			glGetFloatv (pname, vals);
			value result = alloc_array (ints);
			
			for (int i = 0; i < ints; i++) {
				
				val_array_set_i (result, i, alloc_int (vals[i]));
				
			}
			
			return result;
			
		}
		
		return alloc_null ();
		
	}
	
	int GLContext::getError () {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		return glGetError ();
		
	}
	
	int GLContext::getFramebufferAttachmentParameter (int target, int attachment, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint result;
		glGetFramebufferAttachmentParameteriv (target, attachment, pname, &result);
		return result;
		
	}
	
	int GLContext::getProgramParameterInternal (GLProgram* program, int pname) {
		
		GLint result;
		glGetProgramiv (program ? program->id : 0, pname, &result);
		return result;
		
	}
	
	value GLContext::getProgramInfoLogInternal (GLProgram* program) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		GLint logSize;
		GLuint id = program ? program->id : 0;
		glGetProgramiv (id, GL_INFO_LOG_LENGTH, &logSize);
		
		if (logSize <= 0) {
			
			return alloc_string ("");
			
		}
		
		std::vector<GLchar> buf (logSize);
		glGetProgramInfoLog (id, logSize, 0, &buf[0]);
		return alloc_string_len (&buf[0], buf.size ());
		
	}
	
	int GLContext::getRenderbufferParameter (int target, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint result;
		glGetRenderbufferParameteriv (target, pname, &result);
		return result;
		
	}
	
	int GLContext::getShaderParameterInternal (GLShader* shader, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint result;
		glGetShaderiv (shader ? shader->id : 0, pname, &result);
		return result;
		
	}
	
	value GLContext::getShaderPrecisionFormat (int shadertype, int precisiontype) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		
		#ifdef LIME_GLES
		
		int range[2];
		int precision;
		
		glGetShaderPrecisionFormat (shadertype, precisiontype, range, &precision);
		
		value result = alloc_empty_object ();
		alloc_field (result, val_id ("rangeMin"), alloc_int (range[0]));
		alloc_field (result, val_id ("rangeMax"), alloc_int (range[1]));
		alloc_field (result, val_id ("precision"), alloc_int (precision));
		return result;
		
		#else
		
		return alloc_null ();
		
		#endif
		
	}
	
	value GLContext::getShaderInfoLogInternal (GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		GLint logSize;
		GLuint id = shader ? shader->id : 0;
		glGetShaderiv (id, GL_INFO_LOG_LENGTH, &logSize);
		
		if (logSize <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<GLchar> buf (logSize);
		glGetShaderInfoLog (id, logSize, 0, &buf[0]);
		return alloc_string_len (&buf[0], buf.size ());
		
	}
	
	value GLContext::getShaderSourceInternal (GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		GLint len;
		GLuint id = shader ? shader->id : 0;
		glGetShaderiv (id, GL_SHADER_SOURCE_LENGTH, &len);
		
		if (len <= 0) {
			
			return alloc_null ();
			
		}
		
		std::vector<GLchar> buf (len);
		glGetShaderInfoLog (id, len, 0, &buf[0]);
		return alloc_string_len (&buf[0], buf.size ());
		
	}
	
	int GLContext::getTexParameter (int target, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint result;
		glGetTexParameteriv (target, pname, &result);
		return result;
		
	}
	
	value GLContext::getUniformInternal (GLProgram* program, int location) {
		
		if (!checkStatus ()) {
			
			return alloc_null ();
			
		}
		
		
		char buf[1];
		GLsizei outLen;
		GLsizei size;
		GLenum  type;
		GLuint id = program ? program->id : 0;
		
		glGetActiveUniform (id, location, 1, &outLen, &size, &type, buf);
		int ints = 0;
		int floats = 0;
		int bools = 0;
		
		switch (type) {
			
			case GL_FLOAT: {
				
				float result;
				glGetUniformfv (id, location, &result);
				return alloc_float (result);
				
			}
			
			case GL_FLOAT_VEC2: floats = 2;
			case GL_FLOAT_VEC3: floats++;
			case GL_FLOAT_VEC4: floats++;
				break;
			
			case GL_INT_VEC2: ints = 2;
			case GL_INT_VEC3: ints++;
			case GL_INT_VEC4: ints++;
				break;
			
			case GL_BOOL_VEC2: bools = 2;
			case GL_BOOL_VEC3: bools++;
			case GL_BOOL_VEC4: bools++;
				break;
			
			case GL_FLOAT_MAT2: floats = 4; break;
			case GL_FLOAT_MAT3: floats = 9; break;
			case GL_FLOAT_MAT4: floats = 16; break;
			
			#ifdef HX_MACOS
			case GL_FLOAT_MAT2x3: floats = 4 * 3; break;
			case GL_FLOAT_MAT2x4: floats = 4 * 4; break;
			case GL_FLOAT_MAT3x2: floats = 9 * 2; break;
			case GL_FLOAT_MAT3x4: floats = 9 * 4; break;
			case GL_FLOAT_MAT4x2: floats = 16 * 2; break;
			case GL_FLOAT_MAT4x3: floats = 16 * 3; break;
			#endif
			
			case GL_INT:
			case GL_BOOL:
			case GL_SAMPLER_2D:
			#ifdef HX_MACOS
			case GL_SAMPLER_1D:
			case GL_SAMPLER_3D:
			case GL_SAMPLER_CUBE:
			case GL_SAMPLER_1D_SHADOW:
			case GL_SAMPLER_2D_SHADOW:
			#endif
			{
				
				GLint result;
				glGetUniformiv (id, location, &result);
				return alloc_int (result);
				
			}
			
		}
		
		if (ints + bools > 0) {
			
			int buffer[4];
			glGetUniformiv (id, location, buffer);
			
			value result = alloc_array (ints + bools);
			
			for (int i = 0; i < ints + bools; i++) {
				
				val_array_set_i (result, i, alloc_int (buffer[i]));
				
			}
			
			return result;
			
		}
		
		if (floats > 0) {
			
			float buffer[16 * 3];
			glGetUniformfv (id, location, buffer);
			
			value result = alloc_array (floats);
			
			for (int i = 0; i < floats; i++) {
				
				val_array_set_i (result, i, alloc_float (buffer[i]));
				
			}
			
			return result;
			
		}
		
		return alloc_null ();
		
	}
	
	int GLContext::getUniformLocationInternal (GLProgram* program, const char* name) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		return glGetUniformLocation (program ? program->id : 0, name);
		
	}
	
	int GLContext::getVertexAttrib (int index, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		GLint result;
		glGetVertexAttribiv (index, pname, &result);
		return result;
		
	}
	
	int GLContext::getVertexAttribOffset (int index, int pname) {
		
		if (!checkStatus ()) {
			
			return 0;
			
		}
		
		int result = 0;
		glGetVertexAttribPointerv (index, pname, (GLvoid**)&result);
		return result;
		
	}
	
	void GLContext::hint (int target, int mode) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glHint (target, mode);
		
	}
	
	bool GLContext::isBufferInternal (GLBuffer* buffer) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsBuffer (buffer ? buffer->id : 0);
		
	}
	
	bool GLContext::isEnabled (int cap) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsEnabled (cap);
		
	}
	
	bool GLContext::isFramebufferInternal (GLFramebuffer* framebuffer) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsFramebuffer (framebuffer ? framebuffer->id : 0);
		
	}
	
	bool GLContext::isProgramInternal (GLProgram* program) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsProgram (program ? program->id : 0);
		
	}
	
	bool GLContext::isRenderbufferInternal (GLRenderbuffer* renderbuffer) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsRenderbuffer (renderbuffer ? renderbuffer->id : 0);
		
	}
	
	bool GLContext::isShaderInternal (GLShader* shader) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsShader (shader ? shader->id : 0);
		
	}
	
	bool GLContext::isTextureInternal (GLTexture* texture) {
		
		if (!checkStatus ()) {
			
			return false;
			
		}
		
		return glIsTexture (texture ? texture->id : 0);
		
	}
	
	void GLContext::lineWidth (double width) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glLineWidth (width);
		
	}
	
	void GLContext::linkProgramInternal (GLProgram* program) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glLinkProgram (program ? program->id : 0);
		
	}
	
	void GLContext::pixelStorei (int pname, int param) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glPixelStorei (pname, param);
		
	}
	
	void GLContext::polygonOffset (double factor, double units) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glPolygonOffset (factor, units);
		
	}
	
	void GLContext::readPixelsInternal (int x, int y, int width, int height, int format, int type, ArrayBufferView* pixels) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glReadPixels (x, y, width, height, format, type, pixels);
		
	}
	
	void GLContext::renderbufferStorage (int target, int internalformat, int width, int height) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glRenderbufferStorage (target, internalformat, width, height);
		
	}
	
	void GLContext::sampleCoverage (double value, bool invert) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glSampleCoverage (value, invert);
		
	}
	
	void GLContext::scissor (int x, int y, int width, int height) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glScissor (x, y, width, height);
		
	}
	
	void GLContext::shaderSourceInternal (GLShader* shader, HxString& source) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		
		if (source.c_str () == NULL) {
			
			val_throw (alloc_string ("source can't be null"));
			return;
			
		}
		
		const char* str = source.c_str ();
		int length = source.size ();	
		glShaderSource (shader ? shader->id : 0, 1, &str, &length);
		
	}
	
	void GLContext::stencilFunc (int func, int ref, int mask) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilFunc (func, ref, mask);
		
	}
	
	void GLContext::stencilFuncSeparate (int face, int func, int ref, int mask) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilFuncSeparate (face, func, ref, mask);
		
	}
	
	void GLContext::stencilMask (int mask) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilMask (mask);
		
	}
	
	void GLContext::stencilMaskSeparate (int face, int mask) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilMaskSeparate (face, mask);
		
	}
	
	void GLContext::stencilOp (int fail, int zfail, int zpass) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilOp (fail, zfail, zpass);
		
	}
	
	void GLContext::stencilOpSeparate (int face, int fail, int zfail, int zpass) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glStencilOpSeparate (face, fail, zfail, zpass);
		
	}
	
	void GLContext::texImage2DInternal (int target, int level, int internalformat, int width, int height, int border, int format, int type, ArrayBufferView* pixels) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels ? pixels->Data () : NULL);
		
	}
	
	void GLContext::texParameterf (int target, int pname, double param) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glTexParameterf (target, pname, param);
		
	}
	
	void GLContext::texParameteri (int target, int pname, int param) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glTexParameteri (target, pname, param);
		
	}
	
	void GLContext::texSubImage2DInternal (int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, ArrayBufferView* pixels) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glTexSubImage2D (target, level, xoffset, yoffset, width, height, format, type, pixels ? pixels->Data () : NULL);
		
	}
	
	void GLContext::uniform1fInternal (int location, double x) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform1f (location, x);
		
	}
	
	void GLContext::uniform1fvInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 1) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform1fv (location, nbElems, data);
		
	}
	
	void GLContext::uniform1iInternal (int location, int x) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform1i (location, x);
		
	}
	
	void GLContext::uniform1ivInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLint *data = (GLint *)values->Data ();
		int nbElems = size / sizeof (int32_t);
		
		if (nbElems < 1) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform1iv (location, nbElems, data);
		
	}
	
	void GLContext::uniform2fInternal (int location, double x, double y) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform2f (location, x, y);
		
	}
	
	void GLContext::uniform2fvInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 2) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform2fv (location, nbElems / 2, data);
		
	}
	
	void GLContext::uniform2iInternal (int location, int x, int y) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform2i (location, x, y);
		
	}
	
	void GLContext::uniform2ivInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLint *data = (GLint *)values->Data ();
		int nbElems = size / sizeof (int32_t);
		
		if (nbElems < 2) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform2iv (location, nbElems / 2, data);
		
	}
	
	void GLContext::uniform3fInternal (int location, double x, double y, double z) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform3f (location, x, y, z);
		
	}
	
	void GLContext::uniform3fvInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 3) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform3fv (location, nbElems / 3, data);
		
	}
	
	void GLContext::uniform3iInternal (int location, int x, int y, int z) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform3i (location, x, y, z);
		
	}
	
	void GLContext::uniform3ivInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLint *data = (GLint *)values->Data ();
		int nbElems = size / sizeof (int32_t);
		
		if (nbElems < 3) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform3iv (location, nbElems / 3, data);
		
	}
	
	void GLContext::uniform4fInternal (int location, double x, double y, double z, double w) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform4f (location, x, y, z, w);
		
	}
	
	void GLContext::uniform4fvInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 4) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform4fv (location, nbElems / 4, data);
		
	}
	
	void GLContext::uniform4iInternal (int location, int x, int y, int z, int w) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUniform4i (location, x, y, z, w);
		
	}
	
	void GLContext::uniform4ivInternal (int location, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLint *data = (GLint *)values->Data ();
		int nbElems = size / sizeof (int32_t);
		
		if (nbElems < 4) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniform4iv (location, nbElems / 4, data);
		
	}
	
	void GLContext::uniformMatrix2fvInternal (int location, bool transpose, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 4) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniformMatrix2fv (location, nbElems / 4, transpose, data);
		
	}
	
	void GLContext::uniformMatrix3fvInternal (int location, bool transpose, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 9) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniformMatrix3fv (location, nbElems / 9, transpose, data);
		
	}
	
	void GLContext::uniformMatrix4fvInternal (int location, bool transpose, ArrayBufferView *values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		int nbElems = size / sizeof (GLfloat);
		
		if (nbElems < 16) {
			
			val_throw (alloc_string ("Invalid typed array length"));
			return;
			
		}
		
		glUniformMatrix4fv (location, nbElems / 16, transpose, data);
		
	}
	
	void GLContext::useProgramInternal (GLProgram* program) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glUseProgram (program ? program->id : 0);
		
	}
	
	void GLContext::validateProgramInternal (GLProgram* program) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glValidateProgram (program ? program->id : 0);
		
	}
	
	void GLContext::vertexAttrib1f (int indx, double x) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glVertexAttrib1f (indx, x);
		
	}
	
	void GLContext::vertexAttrib1fvInternal (int indx, ArrayBufferView* values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		
		glVertexAttrib1fv (indx, data);
		
	}
	
	void GLContext::vertexAttrib2f (int indx, double x, double y) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glVertexAttrib2f (indx, x, y);
		
	}
	
	void GLContext::vertexAttrib2fvInternal (int indx, ArrayBufferView* values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		
		glVertexAttrib2fv (indx, data);
		
	}
	
	void GLContext::vertexAttrib3f (int indx, double x, double y, double z) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glVertexAttrib3f (indx, x, y, z);
		
	}
	
	void GLContext::vertexAttrib3fvInternal (int indx, ArrayBufferView* values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		
		glVertexAttrib3fv (indx, data);
		
	}
	
	void GLContext::vertexAttrib4f (int indx, double x, double y, double z, double w) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glVertexAttrib4f (indx, x, y, z, w);
		
	}
	
	void GLContext::vertexAttrib4fvInternal (int indx, ArrayBufferView* values) {
		
		if (!checkStatus () || !values) {
			
			return;
			
		}
		
		int size = values->ByteLength ();
		const GLfloat *data = (GLfloat *)values->Data ();
		
		glVertexAttrib4fv (indx, data);
		
	}
	
	void GLContext::vertexAttribPointer (int indx, int size, int type, bool normalized, int stride, int offset) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glVertexAttribPointer (indx, size, type, normalized, stride, (void*)(intptr_t)offset);
		
	}
	
	void GLContext::viewport (int x, int y, int width, int height) {
		
		if (!checkStatus ()) {
			
			return;
			
		}
		
		glViewport (x, y, width, height);
		
	}
	
	bool GLContext::checkStatus () {
		
		if (!context) {
			
			val_throw (alloc_string ("Tried to make OpenGL calls with invalid context"));
			return false;
			
		}
		
		if (!context->MakeCurrent ()) {
			
			val_throw (alloc_string ("Failed to make OpenGL context current"));
			return false;
			
		}
		
		ProcessDeletionQueue ();
		
		return true;
		
	}
	
	void GLContext::ProcessDeletionQueue () {
		
		for (size_t i = 0; i < deletionQueue.size (); ++i) {
			
			GLResource resource = deletionQueue[i];
			switch (resource.type) {
				
				case GL_RESOURCE_BUFFER:
					
					glDeleteBuffers (1, &resource.obj->id);
					break;
					
				case GL_RESOURCE_FRAMEBUFFER:
					
					glDeleteFramebuffers (1, &resource.obj->id);
					break;
					
				case GL_RESOURCE_PROGRAM:
					
					glDeleteProgram (resource.obj->id);
					break;
					
				case GL_RESOURCE_RENDERBUFFER:
					
					glDeleteRenderbuffers (1, &resource.obj->id);
					break;
					
				case GL_RESOURCE_SHADER:
					
					glDeleteShader (resource.obj->id);
					break;
					
				case GL_RESOURCE_TEXTURE:
					
					glDeleteTextures (1, &resource.obj->id);
					break;
					
			}
			
			delete resource.obj;
			
		}
		
		deletionQueue.clear ();
		
	}
	
	void GLContext::ClearDeletionQueue () {
		
		for (size_t i = 0; i < deletionQueue.size (); ++i) {
			
			GLResource resource = deletionQueue[i];
			delete resource.obj;
			
		}
		
		deletionQueue.clear ();
		
	}
	
	void gc_GLContext (value inData) {
		
		GLContext *ctx = (GLContext*)val_data (inData);
		ctx->ReleaseWeakRef ();
		free_abstract (inData);
		
	}
	
	value GLContext_to_val (GLContext *inInstance) {
		
		return CFFIPointer (inInstance, gc_GLContext, Kinds::Get ()->GLContext);
		
	}
	
	GLContext* val_to_GLContext (value inHandle) {
		
		return lime_abstract_to_pointer<GLContext> (inHandle, Kinds::Get ()->GLContext);
		
	}
	
}