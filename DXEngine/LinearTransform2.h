#pragma once
#include "DXEngine.h"
#include "Matrix2.h"

class Vector2;
class DX_API LinearTransform2
{
public:
    LinearTransform2();
    LinearTransform2(const Matrix2& m);

    bool operator == (const LinearTransform2& lt) const;
    bool operator != (const LinearTransform2& lt) const;

    LinearTransform2& Scale(float x, float y);
    LinearTransform2& Scale(const Vector2& v);
    LinearTransform2& Rotate(float angle);
    LinearTransform2& Multiply(const Matrix2& m);

    Matrix2& Matrix2() { return matrix2; }
    const DX_API::Matrix2& Matrix2() const { return matrix2; }

public:
    DX_API::Matrix2 matrix2;
};