#include "GraphicsDevice.h"

using namespace Venus;

namespace GraphicsAPI::Direct3D
{
	VEGraphicsDevice* CreateGraphicsDevice()
	{
		return new GraphicsDevice();
	}
}

GraphicsDevice::GraphicsDevice()
{
    HRESULT hardwareResult = S_OK;
    // 먼저 Factory를 만든다. 넘버링이 올라갈 수록 기능을 더 제공해준다.
    hardwareResult = CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory));


    // 그래픽 카드에 대한 정보들을 roop 돈다. (책 코드에는 loop 사용 없이 가장 첫 번째 그래픽 카드로 설정)
    // Try to create hardware device.
    hardwareResult = D3D12CreateDevice(
        nullptr,             // default adapter
        D3D_FEATURE_LEVEL_12_0,
        IID_PPV_ARGS(&md3dDevice));

    // Fallback to WARP device.
    if (FAILED(hardwareResult))
    {
        IDXGIAdapter* pWarpAdapter;
      
        // 그래픽 카드가 없는 경우 CPU로 GPU처럼 행동하게 만들어준다.
        hardwareResult = mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));

        hardwareResult = D3D12CreateDevice(
            pWarpAdapter,
            D3D_FEATURE_LEVEL_11_0,
            IID_PPV_ARGS(&md3dDevice));
    }
}