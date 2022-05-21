#pragma once
#include "../Venus.h"
#include "VEMatrix2.h"

namespace Venus
{
    class VEVector2;
    class VE_API VELinearTransform2
    {
    public:
        VELinearTransform2();
        VELinearTransform2(const VEMatrix2& m);

        bool operator == (const VELinearTransform2& lt) const;
        bool operator != (const VELinearTransform2& lt) const;

        VELinearTransform2& Scale(float x, float y);
        VELinearTransform2& Scale(const VEVector2& v);
        VELinearTransform2& Rotate(float angle);
        VELinearTransform2& Multiply(const VEMatrix2& m);

        VEMatrix2& Matrix2() { return matrix2; }
        const VEMatrix2& Matrix2() const { return matrix2; }

    public:
        VEMatrix2 matrix2;
    };
}