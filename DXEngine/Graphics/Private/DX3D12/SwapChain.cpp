#include "SwapChain.h"
#include "../../../Window/VEWindow.h"
#include "CommandQueue.h"

using namespace Venus;

SwapChain::SwapChain(GraphicsDevice* device, CommandQueue* queue, const VEWindow* window)
    : width(window->Width())
    , height(window->Height())
    , currBackBuffer(0)
    , swapChain(nullptr)
    , device(nullptr)
{
    DXGI_SWAP_CHAIN_DESC1 desc{};
    desc.Width = width;
    desc.Height = height;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferCount = SwapChainBufferCount;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Scaling = DXGI_SCALING_NONE;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    ComPtr<IDXGISwapChain1> swapChain1;
    ThrowIfFailed(device->Factory()->CreateSwapChainForHwnd(
        queue->Queue(),
        reinterpret_cast<HWND>(window->Handle()),
        &desc,
        nullptr,
        nullptr,
        swapChain1.GetAddressOf()));

    ThrowIfFailed(swapChain1.As(&swapChain));
    currBackBuffer = swapChain->GetCurrentBackBufferIndex();

    for (UINT i = 0; i < SwapChainBufferCount; ++i)
        ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&swapChainBuffer[i])));
}

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