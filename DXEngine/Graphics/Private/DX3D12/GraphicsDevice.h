#pragma once
#include "../../VEGraphicsDevice.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
	class GraphicsDevice final : public VEGraphicsDevice
	{
	public:
		GraphicsDevice();
		~GraphicsDevice() noexcept = default;

		VEObject<VECommandQueue> CreateCommandQueue() override;
		VEObject<VECommandList> CreateCommandList() override;
		VEObject<VEGPUBuffer> CreateGPUBuffer(size_t size, VEGPUBuffer::CPUCacheMode mode) override;
		VEObject<VETexture> CreateTexture(const VETextureDescriptor& descriptor) override;

		ID3D12Device* Device() const { return device.Get(); }
		ComPtr<IDXGIFactory4> Factory() const { return factory; }

	private:
		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory4> factory;
	};
}

