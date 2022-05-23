#pragma once
#include "../Venus.h"
#include "VESwapChain.h"

namespace Venus
{
	class VEWindow;

	class VE_API VECommandQueue
	{
	public:
		VECommandQueue() = default;
		virtual ~VECommandQueue() noexcept = default;

		virtual VESwapChain* CreateSwapChain(const VEWindow*) = 0;
	};

}