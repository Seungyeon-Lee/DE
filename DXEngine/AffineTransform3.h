#pragma once
#include "DXEngine.h"
#include "Matrix3.h"
#include "Vector3.h"

class Matrix4;
class LinearTransform3;
class DX_API AffineTransform3
{
public:
	AffineTransform3();
	AffineTransform3(const Matrix4& m);

	bool operator == (const AffineTransform3& at) const;
	bool operator != (const AffineTransform3& at) const;

	AffineTransform3& Translate(float x, float y, float z);
	AffineTransform3& Translate(const Vector3& v);
	AffineTransform3& Multiply(const LinearTransform3& lt);
	AffineTransform3& Multiply(const AffineTransform3& at);

	Matrix4 Matrix4() const;
	const Matrix3& Matrix3() const { return matrix3; }

public:
	DX_API::Matrix3 matrix3;
	Vector3 translation;
};