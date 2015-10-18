package lime.audio;


import lime.audio.openal.AL;
import lime.audio.openal.ALC;
import lime.audio.openal.ALContext;
import lime.audio.openal.ALDevice;

#if (js && html5)
import js.Browser;
#end


class AudioManager {
	
	
	public static var context:AudioContext;
	
	
	public static function init (context:AudioContext = null) {
		
		if (AudioManager.context == null) {
			
			if (context == null) {
				
				#if (js && html5)
					
					try {
						
						untyped __js__ ("window.AudioContext = window.AudioContext || window.webkitAudioContext;");
						AudioManager.context = WEB (cast untyped __js__ ("new AudioContext ()"));
						
					} catch (e:Dynamic) {
						
						AudioManager.context = HTML5 (new HTML5AudioContext ());
						
					}
					
				#elseif flash
					
					AudioManager.context = FLASH (new FlashAudioContext ());
					
				#elseif lime_console
					
					// TODO
					AudioManager.context = CUSTOM (null);
				
				#else
					
					AudioManager.context = OPENAL (new ALCAudioContext (), new ALAudioContext ());
					
					var device = ALC.openDevice ();
					var ctx = ALC.createContext (device);
					ALC.makeContextCurrent (ctx);
					ALC.processContext (ctx);
					
				#end
				
			} else {
				
				AudioManager.context = context;
				
			}
			
		}
		
	}
	
	
	public static function resume ():Void {
		
		if (context != null) {
			
			switch (context) {
				
				case OPENAL (alc, al):
					
					#if (cpp || neko || nodejs)
					
					var currentContext = alc.getCurrentContext ();
					
					if (currentContext != null) {
						
						var device = alc.getContextsDevice (currentContext);
						ALC.resumeDevice (device);
						alc.processContext (currentContext);
						
					}
					
					#end
				
				default:
				
			}
			
		}
		
	}
	
	
	public static function shutdown ():Void {
		
		if (context != null) {
			
			switch (context) {
				
				case OPENAL (alc, al):
					
					#if (cpp || neko || nodejs)
					
					var currentContext = alc.getCurrentContext ();
					
					if (currentContext != null) {
						
						var device = alc.getContextsDevice (currentContext);
						alc.makeContextCurrent (null);
						alc.destroyContext (currentContext);
						alc.closeDevice (device);
						
					}
					
					#end
				
				default:
				
			}
			
		}
		
	}
	
	
	public static function suspend ():Void {
		
		if (context != null) {
			
			switch (context) {
				
				case OPENAL (alc, al):
					
					#if (cpp || neko || nodejs)
					
					var currentContext = alc.getCurrentContext ();
					
					if (currentContext != null) {
						
						alc.suspendContext (currentContext);
						var device = alc.getContextsDevice (currentContext);
						ALC.pauseDevice (device);
					
					}
					
					#end
				
				default:
				
			}
			
		}
		
	}
	
	
}
