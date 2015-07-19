package lime.video;

import haxe.io.Bytes;
import haxe.io.Path;
import lime.graphics.opengl.GLTexture;
import lime.system.System;
import lime.utils.ByteArray;

typedef VideoCaps =
{
	width:Int,
	height:Int
}

class Video {
	
	private var __handle:Dynamic;

	public function new (handle:Dynamic) {

		__handle = handle;

	}
	
	public function openURL (url:String) {
		
		lime_video_open_url (__handle, url);
		
	}
	
	public function openFile (path:String)
	{
		
		var cwd = Sys.getCwd ();
		var url = "file:///" + Path.join([cwd, path]);
		lime_video_open_url (__handle, url);
		
	}
	
	public function play () {
		
		lime_video_play (__handle);
		
	}
	
	public function setTexture (texture:GLTexture) {
		
		lime_video_set_texture (__handle, texture.id);
		
	}
	
	public var state(get, null):PlayerState;
	@:noCompletion private function get_state():PlayerState
	{
		return cast lime_video_get_state (__handle);
	}
	
	// Native Methods




	#if (cpp || neko || nodejs)
	private static var lime_video_play = System.load ("lime", "lime_video_play", 1);
	private static var lime_video_open_url = System.load ("lime", "lime_video_open_url", 2);
	private static var lime_video_set_texture = System.load ("lime", "lime_video_set_texture", 2);
	private static var lime_video_get_state = System.load("lime", "lime_video_get_state", 1);
	#end


}
