#pragma once
#include "DXEngine.h"
#include "Matrix2.h"
#include "Vector2.h"

class Matrix3;
class LinearTransform2;
class DX_API AffineTransform2
{
public:
	AffineTransform2();
	AffineTransform2(const Matrix3& m);

	bool operator == (const AffineTransform2& at) const;
	bool operator != (const AffineTransform2& at) const;

	AffineTransform2& Translate(float x, float y);
	AffineTransform2& Translate(const Vector2& v);
	AffineTransform2& Multiply(const LinearTransform2& lt);
	AffineTransform2& Multiply(const AffineTransform2& at);

	Matrix3 Matrix3() const;
	const Matrix2& Matrix2() const { return matrix2; }

public:
	DX_API::Matrix2 matrix2;
	Vector2 translation;
};