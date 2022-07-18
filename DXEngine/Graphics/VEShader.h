#include "../Common/VEObject.h"

#pragma once
namespace Venus
{
    class VE_API VEShader : public VERefCounter
    {
    public:
        enum class StageType
        {
            Vertex,
            Fragment,
        };

        VEShader() = default;
        virtual ~VEShader() = default;
    };
}
