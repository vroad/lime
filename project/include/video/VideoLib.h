#ifndef LIME_WMF_VIDEOLIB_H
#define LIME_WMF_VIDEOLIB_H

#include "Video.h"

namespace lime {
	
	
	class VideoLib {
		
		
		public:

			virtual ~VideoLib() {};

			virtual Video *CreateVideo () = 0;
		
		
	};

	VideoLib *CreateVideoLib ();
	
}


#endif