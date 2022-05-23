#include "CommandQueue.h"
#include "SwapChain.h"

using namespace Venus;

CommandQueue::CommandQueue(GraphicsDevice* device, ID3D12CommandQueue* queue)
	: queue(queue)
	, device(device)
{
}

VESwapChain* CommandQueue::CreateSwapChain(const VEWindow* window)
{
	return new SwapChain(device, this, window);
}
