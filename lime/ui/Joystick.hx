package lime.ui;


import lime._internal.utils.CString;
import lime.app.Event;

#if !macro
@:build(lime.system.CFFI.build())
#end


@:cffiInterface("Joystick.xml")
@:cffiCppType("lime::Joystick")
class Joystick {
	
	
	public static var devices = new Map<Int, Joystick> ();
	public static var onConnect = new Event<Joystick->Void> ();
	
	public var connected (default, null):Bool;
	public var guid (get, never):String;
	public var id (default, null):Int;
	public var name (get, never):String;
	public var numAxes (get, never):Int;
	public var numButtons (get, never):Int;
	public var numHats (get, never):Int;
	public var numTrackballs (get, never):Int;
	public var onAxisMove = new Event<Int->Float->Void> ();
	public var onButtonDown = new Event<Int->Void> ();
	public var onButtonUp = new Event<Int->Void> ();
	public var onDisconnect = new Event<Void->Void> ();
	public var onHatMove = new Event<Int->JoystickHatPosition->Void> ();
	public var onTrackballMove = new Event<Int->Float->Void> ();
	
	
	public function new (id:Int) {
		
		this.id = id;
		connected = true;
		
	}
	
	
	@:noCompletion private static function __connect (id:Int):Void {
		
		if (!devices.exists (id)) {
			
			var joystick = new Joystick (id);
			devices.set (id, joystick);
			onConnect.dispatch (joystick);
			
		}
		
	}
	
	
	@:noCompletion private static function __disconnect (id:Int):Void {
		
		var joystick = devices.get (id);
		if (joystick != null) joystick.connected = false;
		devices.remove (id);
		if (joystick != null) joystick.onDisconnect.dispatch ();
		
	}
	
	
	#if (js && html5)
	@:noCompletion private static function __getDeviceData ():Array<Dynamic> {
		
		return (untyped navigator.getGamepads) ? untyped navigator.getGamepads () : (untyped navigator.webkitGetGamepads) ? untyped navigator.webkitGetGamepads () : null;
		
	}
	#end
	
	
	
	
	// Get & Set Methods
	
	
	
	
	@:noCompletion private inline function get_guid ():String {
		
		#if (lime_native && !macro)
		return GetDeviceGUID (this.id);
		#elseif (js && html5)
		var devices = __getDeviceData ();
		return devices[this.id].id;
		#else
		return null;
		#end
		
	}
	
	
	@:noCompletion private inline function get_name ():String {
		
		#if (lime_native && !macro)
		return GetDeviceName (this.id);
		#elseif (js && html5)
		var devices = __getDeviceData ();
		return devices[this.id].id;
		#else
		return null;
		#end
		
	}
	
	
	@:noCompletion private inline function get_numAxes ():Int {
		
		#if (lime_native && !macro)
		return GetNumAxes (this.id);
		#elseif (js && html5)
		var devices = __getDeviceData ();
		return devices[this.id].axes.length;
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private inline function get_numButtons ():Int {
		
		#if (lime_native && !macro)
		return GetNumButtons (this.id);
		#elseif (js && html5)
		var devices = __getDeviceData ();
		return devices[this.id].buttons.length;
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private inline function get_numHats ():Int {
		
		#if (lime_native && !macro)
		return GetNumHats (this.id);
		#else
		return 0;
		#end
		
	}
	
	
	@:noCompletion private inline function get_numTrackballs ():Int {
		
		#if (lime_native && !macro)
		return GetNumTrackballs (this.id);
		#else
		return 0;
		#end
		
	}
	
	
	
	
	// Native Methods
	
	
	
	
	#if (lime_native && !macro)
	@:cffi private static function GetDeviceGUID (id:Int):Dynamic;
	@:cffi private static function GetDeviceName (id:Int):CString;
	@:cffi private static function GetNumAxes (id:Int):Int;
	@:cffi private static function GetNumButtons (id:Int):Int;
	@:cffi private static function GetNumHats (id:Int):Int;
	@:cffi private static function GetNumTrackballs (id:Int):Int;
	#end
	
	
}
