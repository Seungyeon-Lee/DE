#include "VELinearColor.h"
#include "VEColor.h"

using namespace Venus;

VELinearColor::VELinearColor()
    : r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{
}

VELinearColor::VELinearColor(const VEColor& color)
{
    auto inv = 1.0f / 255.0f;
    r = color.r * inv;
    g = color.g * inv;
    b = color.b * inv;
    a = color.a * inv;
}

VELinearColor::VELinearColor(float _r, float _g, float _b)
    : r(Clamp(_r, 0.0f, 1.0f))
    , g(Clamp(_g, 0.0f, 1.0f))
    , b(Clamp(_b, 0.0f, 1.0f))
    , a(1.f)
{
}

VELinearColor::VELinearColor(float _r, float _g, float _b, float _a)
    : r(Clamp(_r, 0.0f, 1.0f))
    , g(Clamp(_g, 0.0f, 1.0f))
    , b(Clamp(_b, 0.0f, 1.0f))
    , a(Clamp(_a, 0.0f, 1.0f))
{
}

bool VELinearColor::operator==(const VELinearColor& c) const
{
    return r == c.r && g == c.g && b == c.b && a == c.a;
}

bool VELinearColor::operator!=(const VELinearColor& c) const
{
    return r != c.r || g != c.g || b != c.b || a != c.a;
}

VELinearColor VELinearColor::operator + (const VELinearColor& c) const
{
    return {
        Clamp(r + c.r, 0.0f, 1.0f),
        Clamp(g + c.g, 0.0f, 1.0f),
        Clamp(b + c.b, 0.0f, 1.0f),
        Clamp(a + c.a, 0.0f, 1.0f)
    };
}

VELinearColor VELinearColor::operator - (const VELinearColor& c) const
{
    return {
        Clamp(r - c.r, 0.0f, 1.0f),
        Clamp(g - c.g, 0.0f, 1.0f),
        Clamp(b - c.b, 0.0f, 1.0f),
        Clamp(a - c.a, 0.0f, 1.0f)
    };
}

VELinearColor VELinearColor::operator * (const VELinearColor& c) const
{
    return {
        Clamp(r * c.r, 0.0f, 1.0f),
        Clamp(g * c.g, 0.0f, 1.0f),
        Clamp(b * c.b, 0.0f, 1.0f),
        Clamp(a * c.a, 0.0f, 1.0f)
    };
}

VELinearColor VELinearColor::operator * (float f) const
{
    return {
        Clamp(r * f, 0.0f, 1.0f),
        Clamp(g * f, 0.0f, 1.0f),
        Clamp(b * f, 0.0f, 1.0f),
        Clamp(a * f, 0.0f, 1.0f)
    };
}

VELinearColor& VELinearColor::operator += (const VELinearColor& c) 
{
    r = Clamp(r + c.r, 0.0f, 1.0f);
    g = Clamp(g + c.g, 0.0f, 1.0f);
    b = Clamp(b + c.b, 0.0f, 1.0f);
    a = Clamp(a + c.a, 0.0f, 1.0f);
    return *this;
}

VELinearColor& VELinearColor::operator -= (const VELinearColor& c) 
{
    r = Clamp(r - c.r, 0.0f, 1.0f);
    g = Clamp(g - c.g, 0.0f, 1.0f);
    b = Clamp(b - c.b, 0.0f, 1.0f);
    a = Clamp(a - c.a, 0.0f, 1.0f);
    return *this;
}

VELinearColor& VELinearColor::operator *= (const VELinearColor& c) 
{
    r = Clamp(r * c.r, 0.0f, 1.0f);
    g = Clamp(g * c.g, 0.0f, 1.0f);
    b = Clamp(b * c.b, 0.0f, 1.0f);
    a = Clamp(a * c.a, 0.0f, 1.0f);
    return *this;
}

VELinearColor& VELinearColor::operator *= (float f) 
{
    r = Clamp(r * f, 0.0f, 1.0f);
    g = Clamp(g * f, 0.0f, 1.0f);
    b = Clamp(b * f, 0.0f, 1.0f);
    a = Clamp(a * f, 0.0f, 1.0f);
    return *this;
}

const VELinearColor VELinearColor::white = VELinearColor(1.f, 1.f, 1.f, 1.f);
const VELinearColor VELinearColor::black = VELinearColor(0.f, 0.f, 0.f, 1.f);
const VELinearColor VELinearColor::red = VELinearColor(1.f, 0.f, 0.f, 1.f);
const VELinearColor VELinearColor::green = VELinearColor(0.f, 1.f, 0.f, 1.f);
const VELinearColor VELinearColor::blue = VELinearColor(0.f, 0.f, 1.f, 1.f);
const VELinearColor VELinearColor::violet = VELinearColor(0.717f, 0.36f, 1.f, 1.f);
