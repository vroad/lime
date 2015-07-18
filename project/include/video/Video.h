#ifndef LIME_VIDEO_VIDEO_H
#define LIME_VIDEO_VIDEO_H


namespace lime {
	
	class Video {
		
		
		public:
			
			virtual ~Video() {};
			
			virtual bool OpenURL (const wchar_t *url) = 0;
			
			virtual bool IsReady () const = 0;
			
			virtual bool Play () = 0;
			
			virtual void SetTexture (unsigned int texture) = 0;
			
	};
	
}


#endif