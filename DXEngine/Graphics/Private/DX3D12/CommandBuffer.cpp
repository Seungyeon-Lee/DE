#include "CommandBuffer.h"
#include "RenderCommandEncoder.h"
#include "CopyCommandEncoder.h"
#include "RenderPipeline.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

CommandBuffer::CommandBuffer(CommandQueue* commandQueue, ID3D12CommandAllocator* allocator, ID3D12GraphicsCommandList* list, D3D12_COMMAND_LIST_TYPE type)
	: type(type)
	, commandQueue(commandQueue)
	, list(list)
	, allocator(allocator)
{
}

VEObject<VERenderCommandEncoder> CommandBuffer::CreateRenderCommandEncoder(VERenderPipeline* pipelineState)
{
	if (RenderPipeline* ps = dynamic_cast<RenderPipeline*>(pipelineState))
	{
		list->Reset(allocator.Get(), ps->PipelineState());
	}
	else
	{
		list->Reset(allocator.Get(), nullptr);
	}
	return new RenderCommandEncoder(this, list.Get());
}

VEObject<VECopyCommandEncoder> CommandBuffer::CreateCopyCommandEncoder()
{
	list->Reset(allocator.Get(), nullptr);
	return new CopyCommandEncoder(this, list.Get());
}

void CommandBuffer::Commit()
{
	ID3D12CommandList* commandLists[] = { list.Get() };
	commandQueue->ExecuteCommandLists(1, commandLists);
}

void CommandBuffer::AddEncodedCommandList(ID3D12GraphicsCommandList* commandList)
{
	// TODO
}

