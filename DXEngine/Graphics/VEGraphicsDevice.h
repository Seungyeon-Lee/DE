#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VECommandQueue.h"
#include "VECommandList.h"
#include "VEGPUBuffer.h"

namespace Venus
{
	class VE_API VEGraphicsDevice : public VERefCounter
	{
	public:
		virtual ~VEGraphicsDevice() noexcept = default;

		virtual VEObject<VECommandQueue> CreateCommandQueue() = 0;
		virtual VEObject<VECommandList> CreateCommandList() = 0;
		virtual VEObject<VEGPUBuffer> CreateGPUBuffer(size_t size, VEGPUBuffer::CPUCacheMode mode) = 0;

		static VEGraphicsDevice* CreateGraphicsDevice();

	protected:
		// User에게 상속을 허용하지 않는다.
		VEGraphicsDevice() = default;
	};
}