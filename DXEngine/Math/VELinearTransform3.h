#pragma once
#include "../Venus.h"
#include "VEMatrix3.h"

namespace Venus
{
    class VEVector3;
    class VE_API VELinearTransform3
    {
    public:
        VELinearTransform3();
        VELinearTransform3(const VEMatrix3& m);

        bool operator == (const VELinearTransform3& lt) const;
        bool operator != (const VELinearTransform3& lt) const;

        VELinearTransform3& Scale(float x, float y, float z);
        VELinearTransform3& Scale(const VEVector3& v);
        VELinearTransform3& RotateX(float angle);
        VELinearTransform3& RotateY(float angle);
        VELinearTransform3& RotateZ(float angle);
        VELinearTransform3& Rotate(const VEVector3& axis, float angle);
        VELinearTransform3& Multiply(const VEMatrix3& m);

        VEMatrix3& Matrix3() { return matrix3; }
        const VEMatrix3& Matrix3() const { return matrix3; }

    public:
        VEMatrix3 matrix3;
    };
}