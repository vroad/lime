#ifndef LIME_UTILS_SAFE_DELETE_H
#define LIME_UTILS_SAFE_DELETE_H

namespace lime {
	
	template <typename T>
	inline void SafeDelete (T *&p){
		
		if (p != NULL) {
			
			delete (p);
			(p) = NULL;
			
		}
		
	}
	
}

#endif