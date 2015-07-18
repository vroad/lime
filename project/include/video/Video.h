#ifndef LIME_VIDEO_VIDEO_H
#define LIME_VIDEO_VIDEO_H


namespace lime {

	enum PlayerState
	{
		Closed = 0,	 	// No session.
		Ready,		  	// Session was created, ready to open a file. 
		OpenPending,	// Session is opening a file.
		Started,		// Session is playing a file.
		Paused,		 	// Session is paused.
		Stopped,		// Session is stopped (ready to play). 
		Closing		 	// Application has closed the session, but is waiting for MESessionClosed.
	};
	
	class Video {
		
		
		public:
			
			virtual ~Video() {};
			
			virtual bool OpenURL (const wchar_t *url) = 0;
			
			virtual PlayerState GetState () const = 0;
			
			virtual bool Play () = 0;
			
			virtual void SetTexture (unsigned int texture) = 0;
			
	};
	
}


#endif