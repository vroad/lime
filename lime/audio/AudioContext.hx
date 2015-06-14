package lime.audio;


import lime.audio.ALAudioContext;
import lime.audio.FlashAudioContext;
import lime.audio.HTML5AudioContext;
import lime.audio.WebAudioContext;

#if lime_shared
@:jsRequire("lime", "lime_audio_AudioContext") extern
#end
enum AudioContext {
	
	OPENAL (alc:ALCAudioContext, al:ALAudioContext);
	HTML5 (context:HTML5AudioContext);
	WEB (context:WebAudioContext);
	FLASH (context:FlashAudioContext);
	CUSTOM (data:Dynamic);
	
}