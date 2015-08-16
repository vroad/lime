//ofxWMFVideoPlayer addon written by Philippe Laulheret for Second Story (secondstory.com)
//Based upon Windows SDK samples
//MIT Licensing



//////////////////////////////////////////////////////////////////////////
//
// PresentEngine.cpp: Defines the D3DPresentEngine object.
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
//
//////////////////////////////////////////////////////////////////////////

#include "EVRPresenter.h"
#include <vector>

HRESULT FindAdapter(IDirect3D9 *pD3D9, HMONITOR hMonitor, UINT *puAdapterID);


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

D3DPresentEngine::D3DPresentEngine(HRESULT& hr) : 
    m_hwnd(NULL),
    m_DeviceResetToken(0),
    m_pD3D9(NULL),
    m_pDevice(NULL),
    m_pDeviceManager(NULL),
    #if 0
    m_pSurfaceRepaint(NULL),
    #endif
    #ifdef NATIVE_TOOLKIT_SDL_ANGLE
    egl_display(NULL),
    egl_surface(NULL),
    #else
    gl_handleD3D(NULL),
    #endif
    d3d_shared_texture(NULL),
    d3d_shared_surface(NULL)
{
    SetRectEmpty(&m_rcDestRect);

    ZeroMemory(&m_DisplayMode, sizeof(m_DisplayMode));

    hr = InitializeD3D();

    if (SUCCEEDED(hr))
    {
       hr = CreateD3DDevice();
    }
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

D3DPresentEngine::~D3DPresentEngine()
{
    #if NATIVE_TOOLKIT_SDL_ANGLE
    releaseSharedTexture ();
    #else
    if (gl_handleD3D) {

        releaseSharedTexture() ;

        printf("WMFVideoPlayer : Killing present engine.....");
        if (wglDXCloseDeviceNV(gl_handleD3D)) 
        {
            printf("SUCCESS\n");
        }
        else printf("FAILED closing handle\n");
    }
    #endif
    SAFE_RELEASE(m_pQuery);
    SAFE_RELEASE(m_pDevice);
    #if 0
    SAFE_RELEASE(m_pSurfaceRepaint);
    #endif
    SAFE_RELEASE(m_pDeviceManager);
    SAFE_RELEASE(m_pD3D9);
}


//-----------------------------------------------------------------------------
// Texture sharing code
//-----------------------------------------------------------------------------

bool D3DPresentEngine::createSharedTexture(unsigned int textureID)
{
    HRESULT hr;
    HANDLE sharedHandle = NULL; //We need to create a shared handle for the ressource, otherwise the extension fails on ATI/Intel cards

    #ifdef NATIVE_TOOLKIT_SDL_ANGLE
    egl_display = lime::eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint numConfigs = 0;
    lime::eglGetConfigs(egl_display, NULL, 0, &numConfigs);
    std::vector<EGLConfig> egl_configs(numConfigs);
    lime::eglGetConfigs(egl_display, &egl_configs[0], numConfigs, &numConfigs);

    EGLint use_rgb = 1;
    lime::eglGetConfigAttrib(egl_display, egl_configs[0], EGL_BIND_TO_TEXTURE_RGB,
        &use_rgb);

    EGLint attrib_list[] = {
        EGL_WIDTH, _w,
        EGL_HEIGHT, _h,
        EGL_TEXTURE_FORMAT, use_rgb ? EGL_TEXTURE_RGB : EGL_TEXTURE_RGBA,
        EGL_TEXTURE_TARGET, EGL_TEXTURE_2D,
        EGL_NONE
    };

    EGLConfig egl_config;
    lime::eglChooseConfig(egl_display, attrib_list, &egl_config, 1, &numConfigs);

    egl_surface = lime::eglCreatePbufferSurface(
        egl_display,
        egl_config,
        attrib_list);

    if (!egl_surface)
    {
        EGLint error = lime::eglGetError();
        printf("egl surface creation failed:%d\n");
        return false;
    }

    HANDLE share_handle = NULL;
    EGLBoolean ret = lime::eglQuerySurfacePointerANGLE(
        egl_display,
        egl_surface,
        EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE,
        &sharedHandle);

    if (!ret)
    {
        lime::eglDestroySurface(egl_display, egl_surface);
        return false;
    }



    #else
    if (gl_handleD3D == NULL )  gl_handleD3D = wglDXOpenDeviceNV(m_pDevice);

    if (!gl_handleD3D)
    {
        printf("openning the shared device failed\nCreate SharedTexture Failed");
        return false;

    }

    gl_name=textureID;
    #endif
    
    hr = m_pDevice->CreateTexture(_w, _h, 1, D3DUSAGE_RENDERTARGET, use_rgb ? D3DFMT_X8R8G8B8 : D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &d3d_shared_texture, &sharedHandle);

    if (FAILED(hr))
    {
        printf("Error creating D3DTexture:%u\n", hr);
        return false;
    }

    if (!sharedHandle)
    {
        printf("Error creating D3D shared handle\n");
        return false;
    }
    
    #ifdef NATIVE_TOOLKIT_SDL_ANGLE

    lime::glEnable(GL_TEXTURE_2D);
    lime::glBindTexture(GL_TEXTURE_2D, textureID);
    lime::eglBindTexImage(egl_display, egl_surface, EGL_BACK_BUFFER);

    d3d_shared_texture->GetSurfaceLevel(0, &d3d_shared_surface);

    #else
    wglDXSetResourceShareHandleNV(d3d_shared_texture,sharedHandle);

    d3d_shared_texture->GetSurfaceLevel(0,&d3d_shared_surface);
        
    gl_handle = wglDXRegisterObjectNV(gl_handleD3D, d3d_shared_texture,
        gl_name,
        GL_TEXTURE_RECTANGLE,
        WGL_ACCESS_READ_ONLY_NV);

    

    

    if (!gl_handle) 
    {
        printf("openning the shared texture failed\nCreate SharedTexture Failed");
        return false;
    }
    #endif
    return true;
}

void D3DPresentEngine::releaseSharedTexture()
{
    #if NATIVE_TOOLKIT_SDL_ANGLE
    lime::eglReleaseTexImage(egl_display, egl_surface, EGL_BACK_BUFFER);
    lime::eglDestroySurface(egl_display, egl_surface);
    egl_display = NULL;
    egl_surface = NULL;
    #else
    if (!gl_handleD3D) return;
    wglDXUnlockObjectsNV(gl_handleD3D, 1, &gl_handle);
    wglDXUnregisterObjectNV(gl_handleD3D,gl_handle);
    //glDeleteTextures(1, &gl_name);
    SAFE_RELEASE(d3d_shared_surface);
    SAFE_RELEASE(d3d_shared_texture);
    #endif

}
bool D3DPresentEngine::lockSharedTexture()
{
    #if 0
    if (!gl_handleD3D) return false;
    if (!gl_handle) return false;
    return wglDXLockObjectsNV(gl_handleD3D, 1, &gl_handle);
    #else
    return true;
    #endif
}

bool D3DPresentEngine::unlockSharedTexture()
{
    #if 0
    if (!gl_handleD3D) return false;
    if (!gl_handle) return false;
    return wglDXUnlockObjectsNV(gl_handleD3D, 1, &gl_handle);
    #else
    return true;
    #endif
}





//-----------------------------------------------------------------------------
// GetService
//
// Returns a service interface from the presenter engine.
// The presenter calls this method from inside it's implementation of 
// IMFGetService::GetService.
//
// Classes that derive from D3DPresentEngine can override this method to return 
// other interfaces. If you override this method, call the base method from the 
// derived class.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::GetService(REFGUID guidService, REFIID riid, void** ppv)
{
    assert(ppv != NULL);

    HRESULT hr = S_OK;

    if (riid == __uuidof(IDirect3DDeviceManager9))
    {
        if (m_pDeviceManager == NULL)
        {
            hr = MF_E_UNSUPPORTED_SERVICE;
        }
        else
        {
            *ppv = m_pDeviceManager;
            m_pDeviceManager->AddRef();
        }
    }
    else
    {
        hr = MF_E_UNSUPPORTED_SERVICE;
    }

    return hr;
}


//-----------------------------------------------------------------------------
// CheckFormat
//
// Queries whether the D3DPresentEngine can use a specified Direct3D format.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::CheckFormat(D3DFORMAT format)
{
    HRESULT hr = S_OK;

    UINT uAdapter = D3DADAPTER_DEFAULT;
    D3DDEVTYPE type = D3DDEVTYPE_HAL;

    D3DDISPLAYMODE mode;
    D3DDEVICE_CREATION_PARAMETERS params;

    if (m_pDevice)
    {
        CHECK_HR(hr = m_pDevice->GetCreationParameters(&params));

        uAdapter = params.AdapterOrdinal;
        type = params.DeviceType;

    }

    CHECK_HR(hr = m_pD3D9->GetAdapterDisplayMode(uAdapter, &mode));

    CHECK_HR(hr = m_pD3D9->CheckDeviceType(uAdapter, type, mode.Format, format, TRUE)); 

done:
    return hr;
}



//-----------------------------------------------------------------------------
// SetVideoWindow
// 
// Sets the window where the video is drawn.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::SetVideoWindow(HWND hwnd)
{
    // Assertions: EVRCustomPresenter checks these cases.
    assert(IsWindow(hwnd));
    assert(hwnd != m_hwnd);     

    HRESULT hr = S_OK;

    AutoLock lock(m_ObjectLock);

    m_hwnd = hwnd;

    UpdateDestRect();

    // Recreate the device.
    hr = CreateD3DDevice();

    return hr;
}

//-----------------------------------------------------------------------------
// SetDestinationRect
// 
// Sets the region within the video window where the video is drawn.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::SetDestinationRect(const RECT& rcDest)
{
    if (EqualRect(&rcDest, &m_rcDestRect))
    {
        return S_OK; // No change.
    }

    HRESULT hr = S_OK;

    AutoLock lock(m_ObjectLock);

    m_rcDestRect = rcDest;

    UpdateDestRect();

    return hr;
}

HRESULT D3DPresentEngine::SetSampleFormat(IMFMediaType *pFormat)
{
    return GetTextureParameters(pFormat, &_w, &_h, &_format);
}

//-----------------------------------------------------------------------------
// CreateVideoSamples
// 
// Creates video samples based on a specified media type.
// 
// pFormat: Media type that describes the video format.
// videoSampleQueue: List that will contain the video samples.
//
// Note: For each video sample, the method creates a swap chain with a
// single back buffer. The video sample object holds a pointer to the swap
// chain's back buffer surface. The mixer renders to this surface, and the
// D3DPresentEngine renders the video frame by presenting the swap chain.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::CreateVideoSamples(
    VideoSampleList& videoSampleQueue
    )
{
    if (m_hwnd == NULL)
    {
        return MF_E_INVALIDREQUEST;
    }

    HRESULT hr = S_OK;

    IMFSample *pVideoSample = NULL;            // Sampl
    
    AutoLock lock(m_ObjectLock);

    ReleaseResources();

    UpdateDestRect();

    // Create the video samples.
    for (int i = 0; i < PRESENTER_BUFFER_COUNT; i++)
    {
        
        // Create the video sample from the swap chain.
        CHECK_HR(hr = CreateD3DSample(&pVideoSample));

        // Add it to the list.
        CHECK_HR(hr = videoSampleQueue.InsertBack(pVideoSample));

        SAFE_RELEASE(pVideoSample);
    }

done:
    if (FAILED(hr))
    {
        ReleaseResources();
    }
    
    SAFE_RELEASE(pVideoSample);
    return hr;
}



//-----------------------------------------------------------------------------
// ReleaseResources
// 
// Released Direct3D resources used by this object. 
//-----------------------------------------------------------------------------

void D3DPresentEngine::ReleaseResources()
{
    // Let the derived class release any resources it created.
    OnReleaseResources();

    #if 0
    SAFE_RELEASE(m_pSurfaceRepaint);
    #endif
}


//-----------------------------------------------------------------------------
// CheckDeviceState
// 
// Tests the Direct3D device state.
//
// pState: Receives the state of the device (OK, reset, removed)
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::CheckDeviceState(DeviceState *pState)
{
    HRESULT hr = S_OK;

    AutoLock lock(m_ObjectLock);

    // Check the device state. Not every failure code is a critical failure.
    hr = m_pDevice->CheckDeviceState(m_hwnd);

    *pState = DeviceOK;

    switch (hr)
    {
    case S_OK:
    case S_PRESENT_OCCLUDED:
      case S_PRESENT_MODE_CHANGED:
        // state is DeviceOK
        hr = S_OK;
        break;

    case D3DERR_DEVICELOST:
    case D3DERR_DEVICEHUNG:
        // Lost/hung device. Destroy the device and create a new one.
        CHECK_HR(hr = CreateD3DDevice());
        *pState = DeviceReset;
        hr = S_OK;
        break;

    case D3DERR_DEVICEREMOVED:
        // This is a fatal error.
        *pState = DeviceRemoved;
        break;

    case E_INVALIDARG:
        // CheckDeviceState can return E_INVALIDARG if the window is not valid
        // We'll assume that the window was destroyed; we'll recreate the device 
        // if the application sets a new window.
        hr = S_OK;
    }

done:
    return hr;
}

//-----------------------------------------------------------------------------
// PresentSample
//
// Presents a video frame.
//
// pSample:  Pointer to the sample that contains the surface to present. If 
//           this parameter is NULL, the method paints a black rectangle.
// llTarget: Target presentation time.
//
// This method is called by the scheduler and/or the presenter.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::PresentSample(IMFSample* pSample, LONGLONG llTarget)
{
    HRESULT hr = S_OK;

#ifdef NATIVE_TOOLKIT_SDL_ANGLE
    IMFMediaBuffer* pBuffer = NULL;
    IDirect3DSurface9* pSurface = NULL;

    if (pSample)
    {
        // Get the buffer from the sample.
        CHECK_HR(hr = pSample->GetBufferByIndex(0, &pBuffer));

        // Get the surface from the buffer.
        CHECK_HR(hr = MFGetService(pBuffer, MR_BUFFER_SERVICE, __uuidof(IDirect3DSurface9), (void**)&pSurface));

        CHECK_HR(hr = m_pDevice->StretchRect(pSurface, NULL, d3d_shared_surface, NULL, D3DTEXF_NONE));

        // Add an end marker to the command buffer queue.
        CHECK_HR(m_pQuery->Issue(D3DISSUE_END));

        // Force the driver to execute the commands from the command buffer.
        // Empty the command buffer and wait until the GPU is idle.
        int iterationCount = 0;
        while(S_FALSE == m_pQuery->GetData(NULL, 0, D3DGETDATA_FLUSH) || iterationCount == 10)
        {
           Sleep(1);
           ++iterationCount;
        }
    }
done:
    SAFE_RELEASE(pSurface);
    SAFE_RELEASE(pBuffer);

    return hr;
#else
#error
#endif
}



//-----------------------------------------------------------------------------
// private/protected methods
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// InitializeD3D
// 
// Initializes Direct3D and the Direct3D device manager.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::InitializeD3D()
{
    HRESULT hr = S_OK;

    assert(m_pD3D9 == NULL);
    assert(m_pDeviceManager == NULL);

    // Create Direct3D
    CHECK_HR(hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D9));

    // Create the device manager
    CHECK_HR(hr = DXVA2CreateDirect3DDeviceManager9(&m_DeviceResetToken, &m_pDeviceManager));

done:
    return hr;
}

//-----------------------------------------------------------------------------
// CreateD3DDevice
// 
// Creates the Direct3D device.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::CreateD3DDevice()
{
    HRESULT     hr = S_OK;
    HWND        hwnd = NULL;
    HMONITOR    hMonitor = NULL;
    UINT        uAdapterID = D3DADAPTER_DEFAULT;
    DWORD       vp = 0;

    D3DCAPS9    ddCaps;
    ZeroMemory(&ddCaps, sizeof(ddCaps));

    IDirect3DDevice9Ex* pDevice = NULL;

    // Hold the lock because we might be discarding an exisiting device.
    AutoLock lock(m_ObjectLock);    

    if (!m_pD3D9 || !m_pDeviceManager)
    {
        return MF_E_NOT_INITIALIZED;
    }

    hwnd = GetDesktopWindow();

    // Note: The presenter creates additional swap chains to present the
    // video frames. Therefore, it does not use the device's implicit 
    // swap chain, so the size of the back buffer here is 1 x 1.

    D3DPRESENT_PARAMETERS pp;
    ZeroMemory(&pp, sizeof(pp));

    pp.BackBufferWidth = 1;
    pp.BackBufferHeight = 1;
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_COPY;
    pp.BackBufferFormat = D3DFMT_UNKNOWN;
    pp.hDeviceWindow = hwnd;
    pp.Flags = D3DPRESENTFLAG_VIDEO;
    pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

    // Find the monitor for this window.
    if (m_hwnd)
    {
        hMonitor = MonitorFromWindow(m_hwnd, MONITOR_DEFAULTTONEAREST);

        // Find the corresponding adapter.
        CHECK_HR(hr = FindAdapter(m_pD3D9, hMonitor, &uAdapterID));
    }

    // Get the device caps for this adapter.
    CHECK_HR(hr = m_pD3D9->GetDeviceCaps(uAdapterID, D3DDEVTYPE_HAL, &ddCaps));

    if(ddCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
    }
    else
    {
        printf("Software cap, no bueno\n");
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }

    // Create the device.
    CHECK_HR(hr = m_pD3D9->CreateDeviceEx(
        uAdapterID,
        D3DDEVTYPE_HAL,
        pp.hDeviceWindow,
        vp | D3DCREATE_NOWINDOWCHANGES | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
        &pp, 
        NULL,
        &pDevice
        ));

    // Get the adapter display mode.
    CHECK_HR(hr = m_pD3D9->GetAdapterDisplayMode(uAdapterID, &m_DisplayMode));

    // Reset the D3DDeviceManager with the new device 
    CHECK_HR(hr = m_pDeviceManager->ResetDevice(pDevice, m_DeviceResetToken));

    // Create the query;
    IDirect3DQuery9* pQuery;
    CHECK_HR(hr = pDevice->CreateQuery(D3DQUERYTYPE_EVENT, &pQuery));

    SAFE_RELEASE(m_pDevice);

    m_pDevice = pDevice;
    m_pDevice->AddRef();

    m_pQuery = pQuery;
    m_pQuery->AddRef();

done:
    SAFE_RELEASE(pDevice);
    SAFE_RELEASE(pQuery);
    return hr;
}


//-----------------------------------------------------------------------------
// CreateD3DSample
//
// Creates an sample object (IMFSample) to hold a Direct3D swap chain.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::CreateD3DSample(IMFSample **ppVideoSample)
{
    // Caller holds the object lock.

    HRESULT hr = S_OK;
    D3DCOLOR clrBlack = D3DCOLOR_ARGB(0xFF, 0x00, 0x00, 0x00);

    IDirect3DSurface9* pSurface = NULL;
    IMFSample* pSample = NULL;

    // Get the back buffer surface.
    HANDLE share_handle = NULL;
    CHECK_HR(hr = m_pDevice->CreateRenderTarget(_w, _h, _format, D3DMULTISAMPLE_NONE, 0, false, &pSurface, &share_handle));

    // Fill it with black.
    CHECK_HR(hr = m_pDevice->ColorFill(pSurface, NULL, clrBlack));

    // Create the sample.
    CHECK_HR(hr = MFCreateVideoSampleFromSurface(pSurface, &pSample));

    // Return the pointer to the caller.
    *ppVideoSample = pSample;
    (*ppVideoSample)->AddRef();

done:
    SAFE_RELEASE(pSurface);
    SAFE_RELEASE(pSample);
    return hr;
}



// PaintFrameWithGDI
// 
// Fills the destination rectangle with black.
//-----------------------------------------------------------------------------
#if 0
void D3DPresentEngine::PaintFrameWithGDI()
{
    HDC hdc = GetDC(m_hwnd);

    if (hdc)
    {
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));

        if (hBrush)
        {
            FillRect(hdc, &m_rcDestRect, hBrush);
            DeleteObject(hBrush);
        }

        ReleaseDC(m_hwnd, hdc);
    }
}
#endif

//-----------------------------------------------------------------------------
// GetTextureParameters
//
// Given a media type that describes the video format, fills in the
// D3DPRESENT_PARAMETERS for creating a swap chain.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::GetTextureParameters(IMFMediaType *pType, UINT *pWidth, UINT *pHeight, D3DFORMAT *pD3DFormat)
{
    // Caller holds the object lock.

    HRESULT hr = S_OK;

    // Helper object for reading the proposed type.
    VideoType videoType(pType);

    if (m_hwnd == NULL)
    {
        return MF_E_INVALIDREQUEST;
    }

    // Get some information about the video format.
    CHECK_HR(hr = videoType.GetFrameDimensions(pWidth, pHeight));
    CHECK_HR(hr = videoType.GetFourCC((DWORD*)pD3DFormat));

done:
    return S_OK;
}


//-----------------------------------------------------------------------------
// UpdateDestRect
//
// Updates the target rectangle by clipping it to the video window's client
// area.
//
// Called whenever the application sets the video window or the destination
// rectangle.
//-----------------------------------------------------------------------------

HRESULT D3DPresentEngine::UpdateDestRect()
{
    if (m_hwnd == NULL)
    {
        return S_FALSE;
    }


    RECT rcView;
    GetClientRect(m_hwnd, &rcView);

    // Clip the destination rectangle to the window's client area.
    if (m_rcDestRect.right > rcView.right)
    {
        m_rcDestRect.right = rcView.right;
    }

    if (m_rcDestRect.bottom > rcView.bottom)
    {
        m_rcDestRect.bottom = rcView.bottom;
    }

    return S_OK;
}

//-----------------------------------------------------------------------------
// Static functions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// FindAdapter
//
// Given a handle to a monitor, returns the ordinal number that D3D uses to 
// identify the adapter.
//-----------------------------------------------------------------------------

HRESULT FindAdapter(IDirect3D9 *pD3D9, HMONITOR hMonitor, UINT *puAdapterID)
{
    HRESULT hr = E_FAIL;
    UINT cAdapters = 0;
    UINT uAdapterID = (UINT)-1;

    cAdapters = pD3D9->GetAdapterCount();
    for (UINT i = 0; i < cAdapters; i++)
    {
        HMONITOR hMonitorTmp = pD3D9->GetAdapterMonitor(i);

        if (hMonitorTmp == NULL)
        {
            break;
        }
        if (hMonitorTmp == hMonitor)
        {
            uAdapterID = i;
            break;
        }
    }

    if (uAdapterID != (UINT)-1)
    {
        *puAdapterID = uAdapterID;
        hr = S_OK;
    }
    return hr;
}
