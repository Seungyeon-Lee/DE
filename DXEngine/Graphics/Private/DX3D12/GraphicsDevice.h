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
		VEObject<VERenderPipeline> CreateRenderPipeline(const VERenderPipelineDescriptor& descriptor) override;

		VEObject<VEGPUBuffer> CreateGPUBuffer(size_t size, VEGPUBuffer::CPUCacheMode mode) override;
		VEObject<VETexture> CreateTexture(const VETextureDescriptor& descriptor) override;

		VEObject<VEShader> CreateShader(const std::vector<uint8_t>& code, const std::string& entry, VEShader::StageType stage) override;

		ID3D12Device* Device() const { return device.Get(); }
		ComPtr<IDXGIFactory4> Factory() const { return factory; }

	private:
		ComPtr<ID3D12Device> device;
		ComPtr<IDXGIFactory4> factory;
	};
}

