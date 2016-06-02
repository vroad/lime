#include <math/Matrix3.h>
#include <utils/StringId.h>


namespace lime {
	
	
	Matrix3::Matrix3 () {
		
		a = 1;
		b = 0;
		c = 0;
		d = 1;
		tx = 0;
		ty = 0;
		
	}
	
	
	Matrix3::Matrix3 (double a, double b, double c, double d, double tx, double ty) {
		
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->tx = tx;
		this->ty = ty;
		
	}
	
	
	Matrix3::Matrix3 (value mat3) {
		
		StringId *id = StringId::Get ();
		
		a = val_number (val_field (mat3, id->a));
		b = val_number (val_field (mat3, id->b));
		c = val_number (val_field (mat3, id->c));
		d = val_number (val_field (mat3, id->d));
		tx = val_number (val_field (mat3, id->tx));
		ty = val_number (val_field (mat3, id->ty));
		
	}
	
	
	value Matrix3::Value () {
		
		StringId *id = StringId::Get ();
		
		value result = alloc_empty_object ();
		alloc_field (result, id->a, alloc_float (a));
		alloc_field (result, id->b, alloc_float (b));
		alloc_field (result, id->c, alloc_float (c));
		alloc_field (result, id->d, alloc_float (d));
		alloc_field (result, id->tx, alloc_float (tx));
		alloc_field (result, id->ty, alloc_float (ty));
		return result;
		
	}
	
	
}