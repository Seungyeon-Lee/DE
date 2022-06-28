#include "RenderPipeline.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

RenderPipeline::RenderPipeline(ID3D12PipelineState* pipelineState, ID3D12RootSignature* rootSignature)
    : pipelineState(pipelineState)
    , rootSignature(rootSignature)
{
}