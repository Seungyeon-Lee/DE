#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VEWindow;
	
	class VE_API VESwapChain : public VERefCounter
	{
	public:
		enum { SwapChainBufferCount = 2 };

		VESwapChain() = default;
		virtual ~VESwapChain() noexcept = default;

		virtual uint32_t Width() = 0;
		virtual uint32_t Height() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;
	};
}
