#include "VEColor.h"

using namespace Venus;

VEColor::VEColor()
    : r(0), g(0), b(0), a(0)
{
}

VEColor::VEColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
    : r(_r), g(_g), b(_b), a(_a)
{
}

VEColor::VEColor(const ARGB& c)
    : r(c.r), g(c.g), b(c.b), a(c.a)
{
}

VEColor::VEColor(const VELinearColor& lc)
{
    r = static_cast<uint8_t>(lc.r * 255.0);
    g = static_cast<uint8_t>(lc.g * 255.0);
    b = static_cast<uint8_t>(lc.b * 255.0);
    a = static_cast<uint8_t>(lc.a * 255.0);
}

bool VEColor::operator == (const VEColor& c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool VEColor::operator != (const VEColor& c) const
{
    return r != c.r || g != c.g || b != c.b || a != c.a;
}

VEColor VEColor::operator + (const VEColor& c) const
{
    return {
        static_cast<uint8_t>(Clamp(r + c.r, 0, 255)),
        static_cast<uint8_t>(Clamp(g + c.g, 0, 255)),
        static_cast<uint8_t>(Clamp(b + c.b, 0, 255)),
        static_cast<uint8_t>(Clamp(a + c.a, 0, 255))
    };
}

VEColor VEColor::operator - (const VEColor& c) const
{
    return {
        static_cast<uint8_t>(Clamp(r - c.r, 0, 255)),
        static_cast<uint8_t>(Clamp(g - c.g, 0, 255)),
        static_cast<uint8_t>(Clamp(b - c.b, 0, 255)),
        static_cast<uint8_t>(Clamp(a - c.a, 0, 255))
    };
}

VEColor& VEColor::operator += (const VEColor& c)
{
    r = static_cast<uint8_t>(Clamp(r + c.r, 0, 255));
    g = static_cast<uint8_t>(Clamp(g + c.g, 0, 255));
    b = static_cast<uint8_t>(Clamp(b + c.b, 0, 255));
    a = static_cast<uint8_t>(Clamp(a + c.a, 0, 255));
    return *this;
}

VEColor& VEColor::operator -= (const VEColor& c)
{
    r = static_cast<uint8_t>(Clamp(r - c.r, 0, 255));
    g = static_cast<uint8_t>(Clamp(g - c.g, 0, 255));
    b = static_cast<uint8_t>(Clamp(b - c.b, 0, 255));
    a = static_cast<uint8_t>(Clamp(a - c.a, 0, 255));
    return *this;
}