//ofxWMFVideoPlayer addon written by Philippe Laulheret for Second Story (secondstory.com)
//Based upon Windows SDK samples
//MIT Licensing


// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#ifndef LIME_WMFVIDEO_H
#define LIME_WMFVIDEO_H

#include <new>
#include <windows.h>
#include <shobjidl.h> 
#include <shlwapi.h>
#include <assert.h>
#include <tchar.h>
#include <strsafe.h>

// Media Foundation headers
#include <mfapi.h>
#include <mfidl.h>
#include <mferror.h>
#include <evr.h>

#include "EVRPresenter.h"
#include <video/Video.h>

namespace lime
{

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

const UINT WM_APP_PLAYER_EVENT = WM_APP + 1;   

    // WPARAM = IMFMediaEvent*, WPARAM = MediaEventType

enum PlayerState
{
    Closed = 0,     // No session.
    Ready,          // Session was created, ready to open a file. 
    OpenPending,    // Session is opening a file.
    Started,        // Session is playing a file.
    Paused,         // Session is paused.
    Stopped,        // Session is stopped (ready to play). 
    Closing         // Application has closed the session, but is waiting for MESessionClosed.
};

class WMFVideo : public IMFAsyncCallback, public Video
{
public:
    static HRESULT CreateInstance(HWND hVideo, HWND hEvent, WMFVideo **ppPlayer);

    // IUnknown methods
    STDMETHODIMP QueryInterface(REFIID iid, void** ppv);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IMFAsyncCallback methods
    STDMETHODIMP  GetParameters(DWORD*, DWORD*)
    {
        // Implementation of this method is optional.
        return E_NOTIMPL;
    }
    STDMETHODIMP  Invoke(IMFAsyncResult* pAsyncResult);

    // Playback
    virtual bool  OpenURL(const wchar_t *url);
    virtual bool  IsReady () const;
    virtual bool  Play ();

    virtual void  SetTexture (unsigned int texture);

    HRESULT       OpenURLInternal(const WCHAR *sURL);
    HRESULT       PlayInternal();
    HRESULT       Pause();
    HRESULT       Stop();
    HRESULT       Shutdown();
    HRESULT       HandleEvent(UINT_PTR pUnkPtr);
    PlayerState   GetState() const { return m_state; }


    
    BOOL          HasVideo() const { return (m_pVideoDisplay != NULL);  }



    float getDuration();
    float getPosition();
    float getWidth() { return _width; }
    float getHeight() { 
        return _height;
    }

    HRESULT setPosition(float pos);

    bool _isLooping;
    bool isLooping() { return _isLooping; }
    void setLooping(bool isLooping) { _isLooping = isLooping; }

    
    HRESULT setVolume(float vol);
    float   getVolume() { return _currentVolume; }

    float getFrameRate();


protected:
    
    // Constructor is private. Use static CreateInstance method to instantiate.
    WMFVideo(HWND hVideo, HWND hEvent);

    // Destructor is private. Caller should call Release.
    virtual ~WMFVideo(); 

    HRESULT Initialize();
    HRESULT CreateSession();
    HRESULT CloseSession();
    HRESULT StartPlayback();


    HRESULT SetMediaInfo( IMFPresentationDescriptor *pPD );

    // Media event handlers
    virtual HRESULT OnTopologyStatus(IMFMediaEvent *pEvent);
    virtual HRESULT OnPresentationEnded(IMFMediaEvent *pEvent);
    virtual HRESULT OnNewPresentation(IMFMediaEvent *pEvent);

    // Override to handle additional session events.
    virtual HRESULT OnSessionEvent(IMFMediaEvent*, MediaEventType) 
    { 
        return S_OK; 
    }

protected:
    long                    m_nRefCount;        // Reference count.

    #if 0
    IMFSequencerSource      *m_pSequencerSource;
    #endif
    IMFMediaSource          *m_pSource;
    IMFVideoDisplayControl  *m_pVideoDisplay;
    MFSequencerElementId    _previousTopoID;
    HWND                    m_hwndVideo;        // Video window.
    HWND                    m_hwndEvent;        // App window to receive events.
    PlayerState             m_state;            // Current state of the media session.
    HANDLE                  m_hCloseEvent;      // Event to wait on while closing.
    IMFAudioStreamVolume    *m_pVolumeControl;

public:
    EVRCustomPresenter      *m_pEVRPresenter; // Custom EVR for texture sharing
    IMFMediaSession         *m_pSession;

protected:
    int _width;
    int _height;
    float _currentVolume;
};

} // namespace lime

#endif LIME_WMFVIDEO_H