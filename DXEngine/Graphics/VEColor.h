#pragma once
#include "../VEInclude.h"

namespace Venus
{
    class VELinearColor;
    class VE_API VEColor
    {
    public:
        struct ARGB
        {
            uint8_t a, r, g, b;
        };

        VEColor();
        VEColor(const ARGB& c);
        VEColor(const VELinearColor& lc);
        VEColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        bool operator == (const VEColor& c) const;
        bool operator != (const VEColor& c) const;

        VEColor operator + (const VEColor& c) const;
        VEColor operator - (const VEColor& c) const;
        
        VEColor& operator += (const VEColor& c);
        VEColor& operator -= (const VEColor& c);

        union
        {
            struct
            {
                uint8_t r, g, b, a;
            };
            uint8_t value[4];
        };
    };
}