#pragma once
#include "DXEngine.h"
#include "Matrix3.h"

class Vector3;
class DX_API LinearTransform3
{
public:
    LinearTransform3();
    LinearTransform3(const Matrix3& m);

    bool operator == (const LinearTransform3& lt) const;
    bool operator != (const LinearTransform3& lt) const;

    LinearTransform3& Scale(float x, float y, float z);
    LinearTransform3& Scale(const Vector3& v);
    LinearTransform3& RotateX(float angle);
    LinearTransform3& RotateY(float angle);
    LinearTransform3& RotateZ(float angle);
    LinearTransform3& Rotate(const Vector3& axis, float angle);
    LinearTransform3& Multiply(const Matrix3& m);

    Matrix3& Matrix3() { return matrix3; }
    const DX_API::Matrix3& Matrix3() const { return matrix3; }

public:
    DX_API::Matrix3 matrix3;
};