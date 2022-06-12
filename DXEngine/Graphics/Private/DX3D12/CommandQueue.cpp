#include "CommandQueue.h"
#include "SwapChain.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

CommandQueue::CommandQueue(GraphicsDevice* device, ID3D12CommandQueue* queue)
	: queue(queue)
	, device(device)
{
}

VEObject<VESwapChain> CommandQueue::CreateSwapChain(const VEWindow* window)
{
	return new SwapChain(device, this, window);
}
