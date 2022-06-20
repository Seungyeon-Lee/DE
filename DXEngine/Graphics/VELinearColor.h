#pragma once
#include "../VEInclude.h"
#include "VEColor.h"

namespace Venus
{
    class VE_API VELinearColor
    {
    public:
        VELinearColor();
        VELinearColor(const VEColor& color);
        VELinearColor(float r, float g, float b);
        VELinearColor(float r, float g, float b, float a);

        bool operator != (const VELinearColor& c) const;
        bool operator == (const VELinearColor& c) const;

        VELinearColor operator + (const VELinearColor& c) const;
        VELinearColor operator - (const VELinearColor& c) const;
        VELinearColor operator * (const VELinearColor& c) const;
        VELinearColor operator * (float f) const;

        VELinearColor& operator += (const VELinearColor& c);
        VELinearColor& operator -= (const VELinearColor& c);
        VELinearColor& operator *= (const VELinearColor& c);
        VELinearColor& operator *= (float f);

        static const VELinearColor white;
        static const VELinearColor black;
        static const VELinearColor red;
        static const VELinearColor green;
        static const VELinearColor blue;

        union
        {
            struct
            {
                float r, g, b, a;
            };
            float value[4];
        };
    };
}
