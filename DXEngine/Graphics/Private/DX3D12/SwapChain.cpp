#include "SwapChain.h"
#include "../../../Window/VEWindow.h"
#include "CommandQueue.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

SwapChain::SwapChain(GraphicsDevice* device, CommandQueue* queue, const VEWindow* window)
    : width(window->Width())
    , height(window->Height())
    , currentTextureIndex(0)
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
    currentTextureIndex = swapChain->GetCurrentBackBufferIndex();

    SetupChainTexture();
    SetupDepthStencil();
}

void SwapChain::SetupChainTexture()
{
    for (UINT i = 0; i < SwapChainBufferCount; ++i)
    {
        // buffer 생성
        ComPtr<ID3D12Resource> buffer;
        ThrowIfFailed(swapChain->GetBuffer(i, IID_PPV_ARGS(&buffer)));
        
        // buffer 상태를 포함하여 Texture 생성
        chainTexture[i] = new Texture(buffer.Get(), D3D12_RESOURCE_STATE_PRESENT);

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask = 0;
        heapDesc.NumDescriptors = 1;

        ComPtr<ID3D12DescriptorHeap> descriptorHeap;
        ThrowIfFailed(device->Device()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

        D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
        rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        device->Device()->CreateRenderTargetView(buffer.Get(), &rtvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
        chainTexture[i]->SetRenderTargetViewHeap(descriptorHeap.Get());
    }
}

void SwapChain::SetupDepthStencil()
{
    VETextureDescriptor desc;
    desc.type = Texture::Type2D;
    desc.format = VEPixelFormat::Depth24UnormStencil8;
    desc.width = width;
    desc.height = height;
    desc.depth = 1;
    desc.mipmapLevelCount = 1;
    desc.sampleCount = 1;
    desc.usage = Texture::UsageDepthStencil;
    depthStencilTexture = device->CreateTexture(desc).DynamicCast<Texture>();
}


void SwapChain::Resize(uint32_t width, uint32_t height) {
    // width나 height에 변경이 있을 때만 적용
    if (this->width != width || this->height != height)
    {
        this->width = width;
        this->height = height;

        // Release the previous resources we will be recreating.
        for (int i = 0; i < SwapChainBufferCount; ++i)
            chainTexture[i] = nullptr;
        depthStencilTexture = nullptr;

        DXGI_SWAP_CHAIN_DESC desc{};
        // Resize the swap chain.
        ThrowIfFailed(swapChain->ResizeBuffers(
            SwapChainBufferCount,
            width, height,
            desc.BufferDesc.Format, // DXGI_FORMAT_R8G8B8A8_UNORM
            desc.Flags)); // DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH

        currentTextureIndex = swapChain->GetCurrentBackBufferIndex();

        SetupChainTexture();
        SetupDepthStencil();
    }
}

const VETexture* SwapChain::CurrentColorTexture() const
{
    return chainTexture[currentTextureIndex];
}

const VETexture* SwapChain::DepthStencilTexture() const
{
    return nullptr;
}

void SwapChain::Present()
{
    ThrowIfFailed(swapChain->Present(0, 0));
    currentTextureIndex = (currentTextureIndex + 1) % SwapChainBufferCount;
}