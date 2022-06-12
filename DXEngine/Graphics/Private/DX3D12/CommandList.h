#pragma once

#include "../../VECommandList.h"
#include "GraphicsDevice.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
	class CommandList final : public VECommandList
	{
    public:
        CommandList(ID3D12CommandAllocator*, ID3D12CommandList*, D3D12_COMMAND_LIST_TYPE);
        ~CommandList() noexcept = default;

        void Reset();

    private:
        D3D12_COMMAND_LIST_TYPE type;
        ComPtr<ID3D12CommandList> list;
        ComPtr<ID3D12CommandAllocator> allocator;
	};
}

