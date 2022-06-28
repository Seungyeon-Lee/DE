#pragma once
#include "../../VERenderPipeline.h"
#include "CommandBuffer.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
    class RenderPipeline final : public VERenderPipeline
    {
    public:
        RenderPipeline(ID3D12PipelineState*, ID3D12RootSignature*);
        ~RenderPipeline() noexcept = default;

        ID3D12PipelineState* PipelineState() const { return pipelineState.Get(); }
        ID3D12RootSignature* RootSignature() const { return rootSignature.Get(); }

    private:
        ComPtr<ID3D12PipelineState> pipelineState;
        ComPtr<ID3D12RootSignature> rootSignature;
    };
}
