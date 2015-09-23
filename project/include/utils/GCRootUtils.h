#ifndef LIME_UTILS_GCROOT_UTILS_H
#define LIME_UTILS_GCROOT_UTILS_H

#include <hx/CFFI.h>
#include <set>

namespace lime {
	
	static std::set<AutoGCRoot*> gRootList;

	static AutoGCRoot *createGCRoot (value inValue) {

		AutoGCRoot *root = new AutoGCRoot (inValue);
		gRootList.insert (root);
		return root;

	}

	static bool removeGCRoot (AutoGCRoot *root) {

		if (!root)
			return false;
		
		std::set<AutoGCRoot*>::const_iterator it = gRootList.find (root);
		if (it != gRootList.end()) {
			
			gRootList.erase (it);
			delete root;
			return true;
			
		}

		return false;

	}

	static void removeAllGCRoot () {

		for (std::set<AutoGCRoot*>::const_iterator it = gRootList.begin(); it != gRootList.end(); ++it)
			delete *it;

		gRootList.clear ();

	}
	
	
}

#endif