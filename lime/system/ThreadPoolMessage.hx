package lime.system;

private class ThreadPoolMessage {
	
	
	public var id:String;
	public var message:Dynamic;
	public var type:ThreadPoolMessageType;
	
	
	public function new (type:ThreadPoolMessageType, id:String, message:Dynamic) {
		
		this.type = type;
		this.id = id;
		this.message = message;
		
	}
	
	
}