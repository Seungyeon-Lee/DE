#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VESwapChain.h"
#include "VECommandBuffer.h"

namespace Venus
{
	class VEWindow;

	class VE_API VECommandQueue : public VERefCounter
	{
	public:
		VECommandQueue() = default;
		virtual ~VECommandQueue() noexcept = default;

		virtual VEObject<VESwapChain> CreateSwapChain(const VEWindow*) = 0;
		virtual VEObject<VECommandBuffer> CreateCommandBuffer() = 0;

		virtual void WaitComplete() = 0;
	};

}