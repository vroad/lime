#ifndef LIME_GRAPHICS_OPENGL_OPENGL_CONTEXT_H
#define LIME_GRAPHICS_OPENGL_OPENGL_CONTEXT_H

#include <graphics/opengl/GLContextHandle.h>
#include <graphics/opengl/GLResource.h>
#include <graphics/opengl/GLResourceType.h>
#include <hx/CFFI.h>
#include <hx/CFFIPrime.h>
#include <ui/Window.h>
#include <vector>
#include <list>

#include "GLObject.h"

namespace lime {
	
	class ArrayBufferView;
		
	class GLContext {
		
	public:
		
		~GLContext ();
		bool Init (value inWindow);
		void AddWeakRef ();
		bool ReleaseWeakRef ();
		bool IsDisposed ();
		void AddGLObjectToDeletionQueue (GLObject* obj, GLResourceType type);
		bool AttachShaderInternal (GLProgram* program, GLShader* shader);
		bool DetachShaderInternal (GLProgram* program, GLShader* shader);
		
		void dispose ();
		
		value getContextAttributes ();
		bool isContextLost ();
		value getSupportedExtensions ();
		value getExtension (const char* name);
		void activeTexture (int texture);
		void attachShaderInternal (GLProgram* program, GLShader* shader);
		void bindAttribLocationInternal (GLProgram* program, int index, const char* name);
		void bindBufferInternal (int target, GLBuffer* buffer);
		void bindFramebufferInternal (int target, GLFramebuffer* framebuffer);
		void bindRenderbufferInternal (int target, GLRenderbuffer* renderbuffer);
		void bindTextureInternal (int target, GLTexture* texture);
		void blendColor (double red, double green, double blue, double alpha);
		void blendEquation (int mode);
		void blendEquationSeparate (int modeRGB, int modeAlpha);
		void blendFunc (int sfactor, int dfactor);
		void blendFuncSeparate (int srcRGB, int dstRGB, int srcAlpha, int dstAlpha);
		void bufferData (int target, ArrayBufferView* data, int usage);
		void bufferSubData (int target, int offset, ArrayBufferView* data);
		int checkFramebufferStatus (int target);
		void clear (int mask);
		void clearColor (double red, double green, double blue, double alpha);
		void clearDepth (double depth);
		void clearStencil (int s);
		void colorMask (bool red, bool green, bool blue, bool alpha);
		void compileShaderInternal (GLShader* shader);
		void compressedTexImage2D (int target, int level, int internalformat, int width, int height, int border, ArrayBufferView* data);
		void compressedTexSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format, ArrayBufferView* data);
		void copyTexImage2D (int target, int level, int internalformat, int x, int y, int width, int height, int border);
		void copyTexSubImage2D (int target, int level, int xoffset, int yoffset, int x, int y, int width, int height);
		static GLContext* createInternal (value inWindow);
		GLBuffer* createBufferInternal ();
		GLFramebuffer* createFramebufferInternal ();
		GLProgram* createProgramInternal ();
		GLRenderbuffer* createRenderbufferInternal ();
		GLShader* createShaderInternal (int type);
		GLTexture* createTextureInternal ();
		void cullFace (int mode);
		void deleteBufferInternal (value inBuffer);
		void deleteFramebufferInternal (value framebuffer);
		void deleteProgramInternal (value program);
		void deleteRenderbufferInternal (value renderbuffer);
		void deleteShaderInternal (value shader);
		void deleteTextureInternal (value texture);
		void depthFunc (int func);
		void depthMask (bool flag);
		void depthRange (double zNear, double zFar);
		void detachShaderInternal (GLProgram* program, GLShader* shader);
		void disable (int cap);
		void disableVertexAttribArray (int index);
		void drawArrays (int mode, int first, int count);
		void drawElements (int mode, int count, int type, int offset);
		void enable (int cap);
		void enableVertexAttribArray (int index);
		void finish ();
		void flush ();
		void framebufferRenderbufferInternal (int target, int attachment, int renderbuffertarget, GLRenderbuffer* renderbuffer);
		void framebufferTexture2DInternal (int target, int attachment, int textarget, GLTexture* texture, int level);
		void frontFace (int mode);
		void generateMipmap (int target);
		value getActiveAttribInternal (GLProgram* program, int index);
		value getActiveUniformInternal (GLProgram* program, int index);
		int getAttribLocationInternal (GLProgram* program, const char* name);
		int getBufferParameter (int target, int pname);
		value getParameter (int pname);
		int getError ();
		int getFramebufferAttachmentParameter (int target, int attachment, int pname);
		int getProgramParameterInternal (GLProgram* program, int pname);
		value getProgramInfoLogInternal (GLProgram* program);
		int getRenderbufferParameter (int target, int pname);
		int getShaderParameterInternal (GLShader* shader, int pname);
		value getShaderPrecisionFormat (int shadertype, int precisiontype);
		value getShaderInfoLogInternal (GLShader* shader);
		value getShaderSourceInternal (GLShader* shader);
		int getTexParameter (int target, int pname);
		value getUniformInternal (GLProgram* program, int location);
		int getUniformLocationInternal (GLProgram* program, const char* name);
		int getVertexAttrib (int index, int pname);
		int getVertexAttribOffset (int index, int pname);
		void hint (int target, int mode);
		bool isBufferInternal (GLBuffer* buffer);
		bool isEnabled (int cap);
		bool isFramebufferInternal (GLFramebuffer* framebuffer);
		bool isProgramInternal (GLProgram* program);
		bool isRenderbufferInternal (GLRenderbuffer* renderbuffer);
		bool isShaderInternal (GLShader* shader);
		bool isTextureInternal (GLTexture* texture);
		void lineWidth (double width);
		void linkProgramInternal (GLProgram* program);
		void pixelStorei (int pname, int param);
		void polygonOffset (double factor, double units);
		void readPixels (int x, int y, int width, int height, int format, int type, ArrayBufferView* pixels);
		void renderbufferStorage (int target, int internalformat, int width, int height);
		void sampleCoverage (double value, bool invert);
		void scissor (int x, int y, int width, int height);
		void shaderSourceInternal (GLShader* shader, HxString& source);
		void stencilFunc (int func, int ref, int mask);
		void stencilFuncSeparate (int face, int func, int ref, int mask);
		void stencilMask (int mask);
		void stencilMaskSeparate (int face, int mask);
		void stencilOp (int fail, int zfail, int zpass);
		void stencilOpSeparate (int face, int fail, int zfail, int zpass);
		void texImage2D (int target, int level, int internalformat, int width, int height, int border, int format, int type, ArrayBufferView* pixels);
		void texParameterf (int target, int pname, double param);
		void texParameteri (int target, int pname, int param);
		void texSubImage2D (int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, ArrayBufferView* pixels);
		void uniform1fInternal (int location, double x);
		void uniform1fvInternal (int location, ArrayBufferView *values);
		void uniform1iInternal (int location, int x);
		void uniform1ivInternal (int location, ArrayBufferView *values);
		void uniform2fInternal (int location, double x, double y);
		void uniform2fvInternal (int location, ArrayBufferView *values);
		void uniform2iInternal (int location, int x, int y);
		void uniform2ivInternal (int location, ArrayBufferView *values);
		void uniform3fInternal (int location, double x, double y, double z);
		void uniform3fvInternal (int location, ArrayBufferView *values);
		void uniform3iInternal (int location, int x, int y, int z);
		void uniform3ivInternal (int location, ArrayBufferView *values);
		void uniform4fInternal (int location, double x, double y, double z, double w);
		void uniform4fvInternal (int location, ArrayBufferView *values);
		void uniform4iInternal (int location, int x, int y, int z, int w);
		void uniform4ivInternal (int location, ArrayBufferView *values);
		void uniformMatrix2fvInternal (int location, bool transpose, ArrayBufferView* values);
		void uniformMatrix3fvInternal (int location, bool transpose, ArrayBufferView* values);
		void uniformMatrix4fvInternal (int location, bool transpose, ArrayBufferView* values);
		void useProgramInternal (GLProgram* program);
		void validateProgramInternal (GLProgram* program);
		void vertexAttrib1f (int indx, double x);
		void vertexAttrib1fvInternal (int indx, ArrayBufferView *values);
		void vertexAttrib2f (int indx, double x, double y);
		void vertexAttrib2fvInternal (int indx, ArrayBufferView *values);
		void vertexAttrib3f (int indx, double x, double y, double z);
		void vertexAttrib3fvInternal (int indx, ArrayBufferView *values);
		void vertexAttrib4f (int indx, double x, double y, double z, double w);
		void vertexAttrib4fvInternal (int indx, ArrayBufferView *values);
		void vertexAttribPointer (int indx, int size, int type, bool normalized, int stride, int offset);
		void viewport (int x, int y, int width, int height);
		
		std::unique_ptr<GLContextHandle> context;
		
	private:
		
		GLContext ();
		bool checkStatus ();
		void ProcessDeletionQueue ();
		void ClearDeletionQueue ();
		
		std::vector<GLResource> deletionQueue;
		int weakRefCount;
		
	};
	
	value GLContext_to_val (GLContext *inInstance);
	
	GLContext* val_to_GLContext (value inHandle);
	
	
}

#endif