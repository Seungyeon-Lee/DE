#pragma once
#include "../../VESwapChain.h"
#include "DXInclude.h"
#include "../../../Common/VEObject.h"
#include "GraphicsDevice.h"

namespace Venus
{
	class VEWindow;
	class CommandQueue;

	class SwapChain final : public VESwapChain
	{
	public:
		SwapChain(GraphicsDevice*, CommandQueue*, const VEWindow*);
		~SwapChain() noexcept = default;

		uint32_t Width() override { return width; }
		uint32_t Height() override { return height; }

		void Resize(uint32_t width, uint32_t height) override;

	private:
		uint32_t width;
		uint32_t height;

		UINT currBackBuffer;
		mutable ComPtr<ID3D12Resource> swapChainBuffer[SwapChainBufferCount];
		mutable ComPtr<ID3D12Resource> depthStencilBuffer;

		ComPtr<IDXGISwapChain3> swapChain;
		VEObject<GraphicsDevice> device;
	};
}
