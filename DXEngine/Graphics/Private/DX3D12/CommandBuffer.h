#pragma once
#include "../../VECommandBuffer.h"
#include "DXInclude.h"
#include "CommandQueue.h"

namespace Venus::Private::Direct3D12
{
	class CommandBuffer final : public VECommandBuffer
	{
	public:
		CommandBuffer(CommandQueue*, ID3D12CommandAllocator*, ID3D12GraphicsCommandList*, D3D12_COMMAND_LIST_TYPE);
		~CommandBuffer() noexcept = default;

		VEObject<VERenderCommandEncoder> CreateRenderCommandEncoder() override;
		VEObject<VECopyCommandEncoder> CreateCopyCommandEncoder() override;

		void Commit() override;

		void AddEncodedCommandList(ID3D12GraphicsCommandList* commandList);

	private:
		std::vector<ComPtr<ID3D12GraphicsCommandList>> encodedCommandList;

		D3D12_COMMAND_LIST_TYPE type;
		VEObject<CommandQueue> commandQueue;
		ComPtr<ID3D12GraphicsCommandList> list;
		ComPtr<ID3D12CommandAllocator> allocator;
	};

}
