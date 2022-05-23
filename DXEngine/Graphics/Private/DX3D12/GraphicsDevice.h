#pragma once
#include "../../VEGraphicsDevice.h"
#include "DXInclude.h"

namespace Venus
{
	class GraphicsDevice final : public VEGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept = default;

		ID3D12Device* Device() const { return md3dDevice.Get(); }

	private:
		ComPtr<ID3D12Device> md3dDevice;
		ComPtr<IDXGIFactory4> mdxgiFactory;
	};
}

