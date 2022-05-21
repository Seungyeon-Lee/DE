#pragma once
#include "../VEGraphicsDevice.h"
#include <dxgi1_4.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "d3dx12.h"

namespace Venus
{
	class GraphicsDevice final : public VEGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept = default;

		ID3D12Device* Device() const { return md3dDevice.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;
		Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	};
}

