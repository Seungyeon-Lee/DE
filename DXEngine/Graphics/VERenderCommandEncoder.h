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

        VERenderCommandEncoder() = default;
        virtual ~VERenderCommandEncoder() noexcept = default;

        virtual void SetViewport(const VEViewport& viewport) = 0;
        virtual void SetViewports(const VEViewport* viewports, uint32_t count) = 0;
        virtual void SetScissorRect(const VERect& rect) = 0;
        virtual void SetScissorRects(const VERect* rects, uint32_t count) = 0;

        virtual void SetRenderTargets(std::vector<const VETexture*> renderTargets, const VETexture* depthStencil) = 0;
        virtual void ClearRenderTargetView(const VETexture* renderTarget, const VELinearColor& clearColor) = 0;
        virtual void ClearDepthStencilView(const VETexture* depthStencil, DepthStencilClearFlag clearFlag, float clearDepth, uint8_t clearStencil) = 0;

        virtual void EndEncoding() = 0;
    };
}