#pragma once
#include "../../VECommandQueue.h"
#include "DXInclude.h"
#include "GraphicsDevice.h"
// #include "../../../Lock/VELock.h"

namespace Venus::Private::Direct3D12
{
	class CommandQueue final : public VECommandQueue
	{
    public:
        // 원시 데이터를 받아서 무언가를 할 수 있게 된다. (helpclass 같은 느낌)
        CommandQueue(GraphicsDevice*, ID3D12CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, ID3D12Fence*);
        ~CommandQueue() noexcept = default;

        VEObject<VESwapChain> CreateSwapChain(const VEWindow*) override;
        VEObject<VECommandBuffer> CreateCommandBuffer() override;

        void WaitComplete() override;

        ID3D12CommandQueue* Queue() const { return queue.Get(); }

        uint64_t ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists);

    private:
        // VESpinLock lock;
        UINT64 currentFenceNumber;
        ComPtr<ID3D12Fence> fence;
        ComPtr<ID3D12CommandQueue> queue;
        GraphicsDevice* device;

        ComPtr<ID3D12CommandAllocator> commandAllocator;
        ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}