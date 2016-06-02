#include <math/Vector2.h>
#include <utils/StringId.h>


namespace lime {
	
	
	Vector2::Vector2 () {
		
		x = 0;
		y = 0;
		
	}
	
	
	Vector2::Vector2 (double x, double y) {
		
		this->x = x;
		this->y = y;
		
	}
	
	
	Vector2::Vector2 (value vec) {
		
		if (!val_is_null (vec)) {
			
			StringId* id = StringId::Get ();
			x = val_number (val_field (vec, id->x));
			y = val_number (val_field (vec, id->y));
			
		} else {
			
			x = 0;
			y = 0;
			
		}
		
	}
	
	
	value Vector2::Value () {
		
		StringId* id = StringId::Get ();
		
		value result = alloc_empty_object ();
		alloc_field (result, id->x, alloc_float (x));
		alloc_field (result, id->y, alloc_float (y));
		return result;
		
	}
	
	
}