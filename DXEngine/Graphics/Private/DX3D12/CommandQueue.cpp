#include "CommandQueue.h"
#include "SwapChain.h"
#include "CommandBuffer.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

CommandQueue::CommandQueue(GraphicsDevice* device,
                           ID3D12CommandQueue* queue,
                           ID3D12CommandAllocator* commandAllocator,
                           ID3D12GraphicsCommandList* commandList,
                           ID3D12Fence* fence)
	: fence(fence)
	, queue(queue)
	, device(device)
	, commandAllocator(commandAllocator)
	, commandList(commandList)
	, currentFenceNumber(0)
{
	ThrowIfFailed(queue->Signal(fence, currentFenceNumber));
}

VEObject<VESwapChain> CommandQueue::CreateSwapChain(const VEWindow* window)
{
	return new SwapChain(device, this, window);
}

VEObject<VECommandBuffer> CommandQueue::CreateCommandBuffer()
{
	return new CommandBuffer(this, commandAllocator.Get(), commandList.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
}

void CommandQueue::WaitComplete()
{
	// VEScopedLock guard(lock);
	ThrowIfFailed(queue->Signal(fence.Get(), ++currentFenceNumber));
	if (fence->GetCompletedValue() < currentFenceNumber)
	{
		HANDLE eventHandle = CreateEvent(nullptr, false, false, nullptr);

		// Fire event when GPU hits current fence.  
		ThrowIfFailed(fence->SetEventOnCompletion(currentFenceNumber, eventHandle));

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

uint64_t CommandQueue::ExecuteCommandLists(uint32_t numCommandLists, ID3D12CommandList* const* commandLists)
{
	// VEScopedLock guard(lock);
	queue->ExecuteCommandLists(numCommandLists, commandLists);
	ThrowIfFailed(queue->Signal(fence.Get(), ++currentFenceNumber));
	return currentFenceNumber;
}
