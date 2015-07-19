package lime.video;

import lime.system.System;

class VideoLib {
	
	private var __handle:Dynamic;

	public function new () {

		#if (cpp || neko || nodejs)
		__handle = lime_video_lib_create ();
		#end

	}

	public function createVideo ():Video {
		
		#if (cpp || neko || nodejs)
		var videoHandle = lime_video_lib_create_video (__handle);
		if (videoHandle != null)
			return new Video (videoHandle);
		else
			return null;
		#end
		
	}


	// Native Methods




	#if (cpp || neko || nodejs)
	private static var lime_video_lib_create = System.load ("lime", "lime_video_lib_create", 0);
	private static var lime_video_lib_create_video = System.load ("lime", "lime_video_lib_create_video", 1);
	#end


}
