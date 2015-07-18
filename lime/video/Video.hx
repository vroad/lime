package lime.video;

import haxe.io.Bytes;
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
    private var __bytes:Dynamic;

	public function new (handle:Dynamic) {

		__handle = handle;

	}
    
    public function openURL (url:String) {
        
        lime_video_open_url (__handle, url);
        
    }
    
    public function isReady ():Bool {
        
        return lime_video_is_ready (__handle);
        
    }
    
    public function play () {
        
        lime_video_play (__handle);
        
    }
    
    public function setTexture (texture:GLTexture) {
        
        lime_video_set_texture (__handle, texture.id);
        
    }
    
    public function uploadToTexture (texture:GLTexture) {
        
        lime_video_upload_to_texture (__handle, texture.id);
        
    }
    
    #if 0
    public function setTextures (backTextures:YUVTexture, foreTextures:YUVTexture) {
        
        lime_video_set_textures (__handle, backTextures.toArray(), foreTextures.toArray());
        
    }
    
    public function lockTexture ():YUVTexture {
        
        var arr:Array<Int> = lime_video_lock_texture (__handle);
        if (arr == null)
            return null;
        return YUVTexture.fromArray (arr);
        
    }
    
    public function unlockTexture () {
        
        lime_video_unlock_texture (__handle);
        
    }
    
    public function getCaps ():VideoCaps {
        
        return lime_video_get_caps (__handle);
        
    }

    public function getVideoSample ():ByteArray {
        
        __bytes = lime_video_get_video_sample (__handle, __bytes);
        var byteArray:ByteArray = ByteArray.fromBytes (@:privateAccess new Bytes (__bytes.length, #if nodejs __bytes.b.buffer #else __bytes.b #end));
	    byteArray.endian = "littleEndian";
        
        return byteArray;
        
    }
    #end

	// Native Methods




	#if (cpp || neko || nodejs)
    private static var lime_video_is_ready = System.load ("lime", "lime_video_is_ready", 1);
    private static var lime_video_play = System.load ("lime", "lime_video_play", 1);
    private static var lime_video_open_url = System.load ("lime", "lime_video_open_url", 2);
    private static var lime_video_set_texture = System.load ("lime", "lime_video_set_texture", 2);
    private static var lime_video_upload_to_texture = System.load ("lime", "lime_video_upload_to_texture", 2);
    #if 0
    private static var lime_video_set_textures = System.load ("lime", "lime_video_set_textures", 3);
	private static var lime_video_lock_texture = System.load ("lime", "lime_video_lock_texture", 1);
	private static var lime_video_unlock_texture = System.load ("lime", "lime_video_unlock_texture", 1);
    private static var lime_video_get_caps = System.load ("lime", "lime_video_get_caps", 1);
	private static var lime_video_get_video_sample = System.load ("lime", "lime_video_get_video_sample", 2);
    private static var lime_video_upload_to_gl = System.load ("lime", "lime_video_upload_to_gl", 2);
    #end
	#end


}
