package lime.video;

@:enum
abstract PlayerState(Int)
{
	var Closed = 0;
	var Ready = 1;
	var OpenPending = 2;
	var Started = 3;
	var Paused = 4;
	var Stopped = 5;
	var Closing = 6;
}