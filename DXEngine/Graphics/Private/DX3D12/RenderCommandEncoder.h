#pragma once
#include "../../VERenderCommandEncoder.h"
#include "DXInclude.h"
#include "CommandBuffer.h"
#include "RenderPipeline.h"

namespace Venus::Private::Direct3D12
{
	class RenderCommandEncoder : public VERenderCommandEncoder
	{
	public:
		RenderCommandEncoder(RenderPipeline*, CommandBuffer*, ID3D12GraphicsCommandList*);
		~RenderCommandEncoder() = default;

		void SetViewport(const VEViewport& viewport) override;
		void SetViewports(const VEViewport* viewports, uint32_t count) override;
		void SetScissorRect(const VERect& rect) override;
		void SetScissorRects(const VERect* rects, uint32_t count) override;

		void SetRenderTargets(std::vector<const VETexture*> renderTargets, const VETexture* depthStencil) override;

		void ClearRenderTargetView(const VETexture* renderTarget, const VELinearColor& clearColor) override;
		void ClearDepthStencilView(const VETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) override;

		void SetVertexBuffer(const VEGPUBuffer* vertexBuffer, uint32_t vertexSize) override;
		void SetIndexBuffer(const VEGPUBuffer* indexBuffer, uint32_t indexSize) override;

		void SetConstantBuffer(uint32_t index, const VEGPUBuffer* constantBuffer) override;

		void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) override;
		void DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart) override;

		void EndEncoding() override;

	private:
		void SetPrimitiveType(PrimitiveType primitiveType);
		void TransitionBufferState(ID3D12Resource* buffer, D3D12_RESOURCE_STATES after, D3D12_RESOURCE_STATES before);

		VEObject<CommandBuffer> commandBuffer;
		ComPtr<ID3D12GraphicsCommandList> commandList;
	};
}