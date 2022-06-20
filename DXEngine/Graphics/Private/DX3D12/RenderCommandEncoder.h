#pragma once
#include "../../VERenderCommandEncoder.h"
#include "CommandBuffer.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
	class RenderCommandEncoder : public VERenderCommandEncoder
	{
	public:
		RenderCommandEncoder(CommandBuffer*, ID3D12GraphicsCommandList*);
		~RenderCommandEncoder() = default;

		void SetViewport(const VEViewport& viewport) override;
		void SetViewports(const VEViewport* viewports, uint32_t count) override;
		void SetScissorRect(const VERect& rect) override;
		void SetScissorRects(const VERect* rects, uint32_t count) override;

		void SetRenderTargets(std::vector<const VETexture*> renderTargets, const VETexture* depthStencil) override;

		void ClearRenderTargetView(const VETexture* renderTarget, const VELinearColor& clearColor) override;
		void ClearDepthStencilView(const VETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;

		void EndEncoding() override;

	private:
		void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

		VEObject<CommandBuffer> commandBuffer;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}