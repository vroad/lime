package lime._backend.html5;
import lime.ui.Window;

class HTML5GLContext {
	
	private function new () {
		
		
		
	}
	
	public static function create (window:Window):HTML5GLContext {
		
		return new HTML5GLContext ();
		
	}
	
	public function makeCurrent (window:Window):Bool {
		
		return true;
		
	}
	
}