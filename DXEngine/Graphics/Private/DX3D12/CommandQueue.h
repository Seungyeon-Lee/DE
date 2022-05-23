#pragma once
#include "../../VECommandQueue.h"
#include "DXInclude.h"
#include "GraphicsDevice.h"

namespace Venus
{
	class CommandQueue final : public VECommandQueue
	{
    public:
        CommandQueue(GraphicsDevice*, ID3D12CommandQueue*);
        ~CommandQueue() noexcept = default;

        VESwapChain* CreateSwapChain(const VEWindow*) override;

        ID3D12CommandQueue* Queue() const { return queue.Get(); }

    private:
        ComPtr<ID3D12CommandQueue> queue;
        GraphicsDevice* device;
	};
}