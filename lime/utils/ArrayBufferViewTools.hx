package lime.utils;


class ArrayBufferViewTools {
	
	
	public static function toAnonArrayBufferView (view:ArrayBufferView):AnonArrayBufferView {
		
		#if js
		var buffer = { length:view.byteLength, b:view };
		return { buffer:buffer, byteLength:view.byteLength, byteOffset:view.byteOffset };
		#else
		return view;
		#end
		
	}
	
	
}