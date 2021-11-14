#pragma once
#include "DXEngine.h"

class VEColor;
class DX_API VELinearColor
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

    union
    {
        struct
        {
            float r, g, b, a;
        };
        float value[4];
    };
};