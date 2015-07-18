#include "WMFVideoLib.h"
#include "WMFVideo.h"
#include <stdio.h>

namespace lime {
	
	WMFVideoLib::WMFVideoLib ()
	{
		initialized = false;
	}

	WMFVideoLib::~WMFVideoLib ()
	{
		Shutdown ();
	}

	bool WMFVideoLib::Initialize ()
	{

		HRESULT hr = MFStartup (MF_VERSION);
		return SUCCEEDED (hr);

	}

	bool WMFVideoLib::Shutdown ()
	{
		if (initialized) {

			MFShutdown ();
			initialized = false;

		}
		return true;
	}

	Video *WMFVideoLib::CreateVideo ()
	{
		PCWSTR szWindowClass = L"MFBASICPLAYBACK" ;
		HWND hwnd;
		WNDCLASSEX wcex;

		// Register the window class.
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbSize         = sizeof(WNDCLASSEX);
		wcex.style          = CS_HREDRAW | CS_VREDRAW;

		wcex.lpfnWndProc    = DefWindowProc;
		wcex.hbrBackground  = (HBRUSH)(BLACK_BRUSH);
		wcex.lpszClassName  = szWindowClass;

		if (RegisterClassEx(&wcex) == 0) {

			return NULL;

		}

		// Create the application window.
		hwnd = CreateWindow(szWindowClass, L"", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, NULL, NULL);

		UpdateWindow (hwnd);
		
		WMFVideo *video = NULL;
		WMFVideo::CreateInstance (hwnd, hwnd, &video);
		return video;
	}

	VideoLib *CreateVideoLib ()
	{
		WMFVideoLib *lib = new WMFVideoLib ();
		bool result = lib->Initialize ();
		if (!result) {

			delete lib;
			return 0;

		}
		return lib;
	}
}