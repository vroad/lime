package lime.utils;


class ArrayBufferViewTools {
	
	
	public static function toAnonArrayBufferView (view:ArrayBufferView):AnonArrayBufferView {
		
		#if js
		if (view != null) {
			
			var buffer = { length:view.byteLength, b:view };
			return { buffer:buffer, byteLength:view.byteLength, byteOffset:view.byteOffset };
			
		} else {
			
			return null;
			
		}
		#else
		return view;
		#end
		
	}
	
	
}

class Float32ArrayTools {
	
	
	public inline static function toAnonArrayBufferView (view:Float32Array):AnonArrayBufferView {
		
		#if js
		return ArrayBufferViewTools.toAnonArrayBufferView (view);
		#else
		return view;
		#end
		
	}
	
	
}

class Int32ArrayTools {
	
	
	public inline static function toAnonArrayBufferView (view:Int32Array):AnonArrayBufferView {
		
		#if js
		return ArrayBufferViewTools.toAnonArrayBufferView (view);
		#else
		return view;
		#end
		
	}
	
	
}