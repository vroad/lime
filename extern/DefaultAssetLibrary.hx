@:native("DefaultAssetLibrary") @:module("lime") extern class DefaultAssetLibrary extends lime.AssetLibrary
{
	function new() : Void;
	var className(default, null) : Map<String, Dynamic>;
	var path(default, null) : Map<String, String>;
	var type(default, null) : Map<String, lime.AssetType>;
	private var lastModified : Float;
	private var timer : haxe.Timer;
	override function exists(id:String, type:String) : Bool;
	override function getAudioBuffer(id:String) : lime.audio.AudioBuffer;
	override function getBytes(id:String) : lime.utils.ByteArray;
	override function getFont(id:String) : lime.text.Font;
	override function getImage(id:String) : lime.graphics.Image;
	override function getPath(id:String) : String;
	override function getText(id:String) : String;
	override function isLocal(id:String, type:String) : Bool;
	override function list(type:String) : Array<String>;
	override function loadAudioBuffer(id:String, handler:lime.audio.AudioBuffer -> Void) : Void;
	override function loadBytes(id:String, handler:lime.utils.ByteArray -> Void) : Void;
	override function loadImage(id:String, handler:lime.graphics.Image -> Void) : Void;
	private function loadManifest() : Void;
	override function loadText(id:String, handler:String -> Void) : Void;
}