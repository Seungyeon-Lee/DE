#pragma once
#include "../../VECommandQueue.h"
#include "DXInclude.h"
#include "GraphicsDevice.h"

namespace Venus::Private::Direct3D12
{
	class CommandQueue final : public VECommandQueue
	{
    public:
        // 원시 데이터를 받아서 무언가를 할 수 있게 된다. (helpclass 같은 느낌)
        CommandQueue(GraphicsDevice*, ID3D12CommandQueue*);
        ~CommandQueue() noexcept = default;

        VEObject<VESwapChain> CreateSwapChain(const VEWindow*) override;

        ID3D12CommandQueue* Queue() const { return queue.Get(); }

    private:
        ComPtr<ID3D12CommandQueue> queue;
        GraphicsDevice* device;
	};
}