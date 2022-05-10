#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "CommonUtil.h"
class DXApp
{
protected:

    DXApp(HINSTANCE hInstance);
    DXApp(const DXApp& rhs) = delete;
    DXApp& operator=(const DXApp& rhs) = delete;
    virtual ~DXApp();

public:

    static DXApp* GetApp();
    
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;

	int Run();
 
    virtual bool Initialize();
    virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	virtual void Update()=0;
    virtual void Draw()=0;

protected:

	bool InitMainWindow();
	bool InitDirect3D();

protected:

    static DXApp* mApp;

    HINSTANCE mhAppInst = nullptr; // application instance handle
    HWND      mhMainWnd = nullptr; // main window handle
	bool      mAppPaused = false;  // is the application paused?
	bool      mMinimized = false;  // is the application minimized?
	bool      mMaximized = false;  // is the application maximized?
	bool      mResizing = false;   // are the resize bars being dragged?
    bool      mFullscreenState = false;// fullscreen enabled

    Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption = L"d3d App";
	D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
    DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int mClientWidth = 800;
	int mClientHeight = 600;
};

