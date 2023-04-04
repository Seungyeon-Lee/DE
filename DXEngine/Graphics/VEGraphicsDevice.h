#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VECommandQueue.h"
#include "VEGPUBuffer.h"
#include "VETexture.h"
#include "VEShader.h"
#include "VERenderPipeline.h"
#include <vector>
#include <string>

namespace Venus
{
	class VE_API VEGraphicsDevice : public VERefCounter
	{
	public:
		virtual ~VEGraphicsDevice() noexcept = default;

		virtual VEObject<VECommandQueue> CreateCommandQueue() = 0;
		virtual VEObject<VERenderPipeline> CreateRenderPipeline(const VERenderPipelineDescriptor& descriptor) = 0;
		virtual VEObject<VEGPUBuffer> CreateGPUBuffer(size_t size, VEGPUBuffer::CPUCacheMode mode) = 0;
		virtual VEObject<VETexture> CreateTexture(const VETextureDescriptor& descriptor) = 0;

		static VEGraphicsDevice* CreateGraphicsDevice();

		virtual VEObject<VEShader> CreateShader(const std::wstring& path, const std::string& entry, VEShader::StageType stage);
		virtual VEObject<VEShader> CreateShader(const std::vector<uint8_t>& path, const std::string& entry, VEShader::StageType stage) = 0;
	protected:
		// User에게 상속을 허용하지 않는다.
		VEGraphicsDevice() = default;
	};
}