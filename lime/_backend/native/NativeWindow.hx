package lime._backend.native;


import lime._internal.utils.CString;
import lime.app.Application;
import lime.graphics.Image;
import lime.graphics.ImageBuffer;
import lime.math.Vector2;
import lime.system.Display;
import lime.system.System;
import lime.ui.Window;

#if !macro
@:build(lime.system.CFFI.build())
#end

@:access(lime.app.Application)
@:access(lime.ui.Window)


@:cffiInterface("Window.xml")
@:cffiCppType("lime::Window")
class NativeWindow {
	
	
	@:cffiHandle public var handle (default, null):Dynamic;
	
	private var closing:Bool;
	private var parent:Window;
	
	
	public function new (parent:Window) {
		
		this.parent = parent;
		
	}
	
	
	public function alert (message:String, title:String):Void {
		
		if (handle != null) {
			
			#if !macro
			Alert (message, title);
			#end
			
		}
		
	}
	
	
	public function close ():Void {
		
		if (!closing) {
			
			closing = true;
			parent.onClose.dispatch ();
			
		}
		
		if (!parent.onClose.canceled) {
			
			if (handle != null) {
				
				#if !macro
				Close ();
				#end
				handle = null;
				
			}
			
		} else {
			
			closing = false;
			
		}
		
	}
	
	
	public function create (application:Application):Void {
		
		var title = "Lime Application";
		var flags = 0;
		
		if (parent.config != null) {
			
			if (Reflect.hasField (parent.config, "antialiasing")) {
				
				if (parent.config.antialiasing >= 4) {
					
					flags |= cast WindowFlags.WINDOW_FLAG_HW_AA_HIRES;
					
				} else if (parent.config.antialiasing >= 2) {
					
					flags |= cast WindowFlags.WINDOW_FLAG_HW_AA;
					
				}
				
			}
			
			if (Reflect.hasField (parent.config, "allowHighDPI") && parent.config.allowHighDPI) flags |= cast WindowFlags.WINDOW_FLAG_ALLOW_HIGHDPI;
			if (Reflect.hasField (parent.config, "borderless") && parent.config.borderless) flags |= cast WindowFlags.WINDOW_FLAG_BORDERLESS;
			if (Reflect.hasField (parent.config, "depthBuffer") && parent.config.depthBuffer) flags |= cast WindowFlags.WINDOW_FLAG_DEPTH_BUFFER;
			if (Reflect.hasField (parent.config, "fullscreen") && parent.config.fullscreen) flags |= cast WindowFlags.WINDOW_FLAG_FULLSCREEN;
			if (Reflect.hasField (parent.config, "hardware") && parent.config.hardware) flags |= cast WindowFlags.WINDOW_FLAG_HARDWARE;
			if (Reflect.hasField (parent.config, "resizable") && parent.config.resizable) flags |= cast WindowFlags.WINDOW_FLAG_RESIZABLE;
			if (Reflect.hasField (parent.config, "stencilBuffer") && parent.config.stencilBuffer) flags |= cast WindowFlags.WINDOW_FLAG_STENCIL_BUFFER;
			if (Reflect.hasField (parent.config, "vsync") && parent.config.vsync) flags |= cast WindowFlags.WINDOW_FLAG_VSYNC;
			
			if (Reflect.hasField (parent.config, "title")) {
				
				title = parent.config.title;
				
			}
			
		}
		
		#if !macro
		handle = Create (application.backend.handle, parent.width, parent.height, flags, title);
		
		if (handle == null) {
			
			throw "Failed to create window";
			
		}
		
		parent.__width = GetWidth ();
		parent.__height = GetHeight ();
		parent.__x = GetX ();
		parent.__y = GetY ();
		parent.id = GetID ();
		
		#end
		
	}
	
	
	public function focus ():Void {
		
		if (handle != null) {
			
			#if !macro
			Focus ();
			#end
			
		}
		
	}
	
	
	public function getDisplay ():Display {
		
		if (handle != null) {
			
			#if !macro
			var index = GetDisplay ();
			
			if (index > -1) {
				
				return System.getDisplay (index);
				
			}
			#end
			
		}
		
		return null;
		
	}
	
	
	public function getEnableTextEvents ():Bool {
		
		if (handle != null) {
			
			#if !macro
			return GetEnableTextEvents ();
			#end
			
		}
		
		return false;
		
	}
	
	
	public function move (x:Int, y:Int):Void {
		
		if (handle != null) {
			
			#if !macro
			Move (x, y);
			#end
			
		}
		
	}
	
	
	public function resize (width:Int, height:Int):Void {
		
		if (handle != null) {
			
			#if !macro
			Resize (width, height);
			#end
			
		}
		
	}
	
	
	public function setBorderless (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetBorderless (value);
			#end
			
		}
		
		return value;
	}
	
	
	public function setEnableTextEvents (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetEnableTextEvents (value);
			#end
			
		}
		
		return value;
		
	}
	
	
	public function setFullscreen (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetFullscreen (value);
			
			parent.__width = GetWidth ();
			parent.__height = GetHeight ();
			parent.__x = GetX ();
			parent.__y = GetY ();
			
			if (value) {
				
				parent.onFullscreen.dispatch ();
				
			}
			#end
			
		}
		
		return value;
		
	}
	
	
	public function setIcon (image:Image):Void {
		
		if (handle != null) {
			
			#if !macro
			SetIcon (image.buffer);
			#end
			
		}
		
	}
	
	
	public function setMaximized (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetMaximized (value);
			#end
			
		}
		
		return value;
		
	}
	
	
	public function setMinimized (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetMinimized (value);
			#end
			
		}
		
		return value;
		
	}
	
	
	public function setResizable (value:Bool):Bool {
		
		if (handle != null) {
			
			#if !macro
			SetResizable (value);
			
			// TODO: remove need for workaround
			
			SetBorderless (!parent.__borderless);
			SetBorderless (parent.__borderless);
			#end
			
		}
		
		return value;
	}
	
	
	public function setTitle (value:String):String {
		
		if (handle != null) {
			
			#if !macro
			SetTitle (value);
			#end
			
		}
		
		return value;
		
	}
	
	
	public function swapWindow ():Void {
		
		#if !macro
		SwapWindow ();
		#end
		
	}
	
	
	#if !macro
	@:cffi private function Alert (message:CString, title:CString):Void;
	@:cffi @:cffiFreeAbstract private function Close ():Void;
	@:cffi private static function Create (application:ApplicationHandle, width:Int, height:Int, flags:Int, title:CString):WindowHandle;
	@:cffi private function Focus ():Void;
	@:cffi private function GetDisplay ():Int;
	@:cffi private function GetEnableTextEvents ():Bool;
	@:cffi private function GetHeight ():Int;
	@:cffi private function GetID ():Int;
	@:cffi private function GetWidth ():Int;
	@:cffi private function GetX ():Int;
	@:cffi private function GetY ():Int;
	@:cffi private function Move (x:Int, y:Int):Void;
	@:cffi private function Resize (width:Int, height:Int):Void;
	@:cffi private function SetBorderless (borderless:Bool):Void;
	@:cffi private function SetEnableTextEvents (enabled:Bool):Void;
	@:cffi private function SetFullscreen (fullscreen:Bool):Void;
	@:cffi private function SetIcon (buffer:ImageBuffer):Void;
	@:cffi private function SetMaximized (maximized:Bool):Void;
	@:cffi private function SetMinimized (minimized:Bool):Void;
	@:cffi private function SetResizable (resizable:Bool):Void;
	@:cffi private function SetTitle (title:CString):Void;
	@:cffi private function SwapWindow ():Void;
	#end
	
	
}


@:enum private abstract WindowFlags(Int) {
	
	var WINDOW_FLAG_FULLSCREEN = 0x00000001;
	var WINDOW_FLAG_BORDERLESS = 0x00000002;
	var WINDOW_FLAG_RESIZABLE = 0x00000004;
	var WINDOW_FLAG_HARDWARE = 0x00000008;
	var WINDOW_FLAG_VSYNC = 0x00000010;
	var WINDOW_FLAG_HW_AA = 0x00000020;
	var WINDOW_FLAG_HW_AA_HIRES = 0x00000060;
	var WINDOW_FLAG_ALLOW_SHADERS = 0x00000080;
	var WINDOW_FLAG_REQUIRE_SHADERS = 0x00000100;
	var WINDOW_FLAG_DEPTH_BUFFER = 0x00000200;
	var WINDOW_FLAG_STENCIL_BUFFER = 0x00000400;
	var WINDOW_FLAG_ALLOW_HIGHDPI = 0x00000800;
	
}