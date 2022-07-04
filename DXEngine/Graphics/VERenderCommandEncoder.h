#pragma once
#include "../VEInclude.h"
#include "VEViewport.h"
#include "VELinearColor.h"
#include "../Math/VEMath.h"
#include "../Common/VEObject.h"
#include <vector>

namespace Venus
{
    class VETexture;
    class VEGPUBuffer;

    class VE_API VERenderCommandEncoder : public VERefCounter
    {
    public:
        enum class DepthStencilClearFlag
        {
            Depth,
            Stencil,
            All,
        };

        enum class PrimitiveType
        {
            Point,
            Line,
            LineStrip,
            Triangle,
            TriangleStrip,
        };

        VERenderCommandEncoder() = default;
        virtual ~VERenderCommandEncoder() noexcept = default;

        virtual void SetViewport(const VEViewport& viewport) = 0;
        virtual void SetViewports(const VEViewport* viewports, uint32_t count) = 0;
        virtual void SetScissorRect(const VERect& rect) = 0;
        virtual void SetScissorRects(const VERect* rects, uint32_t count) = 0;

        virtual void SetRenderTargets(std::vector<const VETexture*> renderTargets, const VETexture* depthStencil) = 0;
        virtual void ClearRenderTargetView(const VETexture* renderTarget, const VELinearColor& clearColor) = 0;
        virtual void ClearDepthStencilView(const VETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;

        virtual void SetVertexBuffer(const VEGPUBuffer* vertexBuffer, uint32_t vertexSize) = 0;
        virtual void SetIndexBuffer(const VEGPUBuffer* indexBuffer, uint32_t indexSize) = 0;

        virtual void SetConstantBuffer(uint32_t index, const VEGPUBuffer* constantBuffer) = 0;

        virtual void DrawPrimitives(PrimitiveType primitiveType, uint32_t vertexCount, uint32_t instanceCount, uint32_t vertexStart, uint32_t instanceStart) = 0;
        virtual void DrawIndexedPrimitives(PrimitiveType primitiveType, uint32_t indexCount, uint32_t instanceCount, uint32_t indexOffset, uint32_t vertexOffset, uint32_t instanceStart) = 0;

        virtual void EndEncoding() = 0;
    };
}