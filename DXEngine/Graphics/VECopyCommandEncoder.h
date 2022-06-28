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

    class VE_API VECopyCommandEncoder : public VERefCounter
    {
    public:
        VECopyCommandEncoder() = default;
        virtual ~VECopyCommandEncoder() noexcept = default;

        virtual void CopyBufferToBuffer(VEGPUBuffer* src, size_t srcOffset, VEGPUBuffer* dest, size_t destOffset, size_t copySize) = 0;
        virtual void EndEncoding() = 0;
    };
}