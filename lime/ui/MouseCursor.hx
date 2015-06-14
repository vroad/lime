package lime.ui;

#if lime_shared
@:jsRequire("lime", "lime_ui_MouseCursor") extern
#end
enum MouseCursor {
	
	ARROW;
	CROSSHAIR;
	DEFAULT;
	MOVE;
	POINTER;
	RESIZE_NESW;
	RESIZE_NS;
	RESIZE_NWSE;
	RESIZE_WE;
	TEXT;
	WAIT;
	WAIT_ARROW;
	CUSTOM;
	
}