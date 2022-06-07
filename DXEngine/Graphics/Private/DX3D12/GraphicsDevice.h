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

		VECommandQueue* CreateCommandQueue() override;
		VECommandList* CreateCommandList() override;

		ID3D12Device* Device() const { return device.Get(); }
		ComPtr<IDXGIFactory4> Factory() const { return factory; }

	private:
		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory4> factory;
	};
}

