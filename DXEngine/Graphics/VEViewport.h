#pragma once
#include "../VEInclude.h"
#include "../Math/VEMath.h"

namespace Venus
{
    class VEViewport final
    {
    public:
        VEViewport();
        VEViewport(VEPoint origin, VESize size, float nearDepth, float farDepth);
        VEViewport(float x, float y, float width, float height, float nearDepth, float farDepth);

        union
        {
            struct
            {
                VEPoint origin;
                VESize size;
                float nearDepth;
                float farDepth;
            };
            struct
            {
                float x, y;
                float width, height;
            };
        };
    };
}