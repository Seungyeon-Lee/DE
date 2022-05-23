#include "SwapChain.h"

using namespace Venus;

void SwapChain::Resize(uint32_t width, uint32_t height) {
	// Release the previous resources we will be recreating.
	for (int i = 0; i < SwapChainBufferCount; ++i)
		swapChainBuffer[i].Reset();
	depthStencilBuffer.Reset();

	DXGI_SWAP_CHAIN_DESC desc{};
	// Resize the swap chain.
	ThrowIfFailed(swapChain->ResizeBuffers(
		SwapChainBufferCount,
		width, height,
		desc.BufferDesc.Format, // DXGI_FORMAT_R8G8B8A8_UNORM
		desc.Flags)); // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH

	currBackBuffer = swapChain->GetCurrentBackBufferIndex();

	for (UINT i = 0; i < SwapChainBufferCount; i++)
		ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer[i])));

}