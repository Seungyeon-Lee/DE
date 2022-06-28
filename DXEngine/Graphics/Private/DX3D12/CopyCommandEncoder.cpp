#include "CopyCommandEncoder.h"
#include "Texture.h"
#include "GPUBuffer.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

CopyCommandEncoder::CopyCommandEncoder(CommandBuffer* commandBuffer, ID3D12GraphicsCommandList* commandList)
	: commandBuffer(commandBuffer)
	, commandList(commandList)
{
}

void CopyCommandEncoder::EndEncoding()
{
	commandList->Close();
	commandBuffer->AddEncodedCommandList(commandList.Get());
	commandList = nullptr;
}

void CopyCommandEncoder::CopyBufferToBuffer(VEGPUBuffer* src, size_t srcOffset, VEGPUBuffer* dest, size_t destOffset, size_t copySize)
{
    GPUBuffer* srcBuffer = dynamic_cast<GPUBuffer*>(src);
    GPUBuffer* destBuffer = dynamic_cast<GPUBuffer*>(dest);

    ID3D12Resource* srcRawBuffer = srcBuffer->Buffer();
    ID3D12Resource* destRawBuffer = destBuffer->Buffer();

    TransitionBufferState(destRawBuffer, destBuffer->InitialState(), D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->CopyBufferRegion(destRawBuffer, destOffset, srcRawBuffer, srcOffset, copySize);
    TransitionBufferState(destRawBuffer, D3D12_RESOURCE_STATE_COPY_DEST, destBuffer->InitialState());
}


void CopyCommandEncoder::TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before)
{
	if (before != after)
	{
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(buffer, before, after);
		commandList->ResourceBarrier(1, &barrier);
	}
}
