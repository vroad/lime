#ifndef LIME_WMF_VIDEO_LIB_H
#define LIME_WMF_VIDEO_LIB_H

#include <video/VideoLib.h>
#include <video/Video.h>
#include <Mfapi.h>

namespace lime {
	
	
	class WMFVideoLib : public VideoLib {
		
		
		public:
			
			WMFVideoLib ();

			virtual ~WMFVideoLib ();

			bool Initialize ();

			bool Shutdown ();
			
			virtual Video *CreateVideo ();

		private:
		
			bool initialized;
		
	};
	
}


#endif