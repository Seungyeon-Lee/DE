#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VESwapChain.h"

namespace Venus
{
	class VEWindow;

	class VE_API VECommandQueue : public VERefCounter
	{
	public:
		VECommandQueue() = default;
		virtual ~VECommandQueue() noexcept = default;

		virtual VEObject<VESwapChain> CreateSwapChain(const VEWindow*) = 0;
	};

}