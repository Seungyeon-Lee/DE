#pragma once
#include "../../VECopyCommandEncoder.h"
#include "CommandBuffer.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
	class CopyCommandEncoder : public VECopyCommandEncoder
	{
	public:
		CopyCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
		~CopyCommandEncoder() = default;

		void CopyBufferToBuffer(VEGPUBuffer* src, size_t srcOffset, VEGPUBuffer* dest, size_t destOffset, size_t copySize) override;
		void EndEncoding() override;

	private:
		void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

		VEObject<CommandBuffer> commandBuffer;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}