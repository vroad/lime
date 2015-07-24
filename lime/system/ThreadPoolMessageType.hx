package lime.system;

#if lime_shared
@:jsRequire("lime", "lime_system_ThreadPoolMessageType") extern
#end
enum ThreadPoolMessageType {
	
	COMPLETE;
	ERROR;
	EXIT;
	PROGRESS;
	WORK;
	
}