package lime.system;

class ThreadPoolMessage {
	
	public var state:Dynamic;
	public var type:ThreadPoolMessageType;
	
	
	public function new (type:ThreadPoolMessageType, state:Dynamic) {
		
		this.type = type;
		this.state = state;
		
	}
	
	
}
