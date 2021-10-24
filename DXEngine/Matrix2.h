#pragma once
#include "DXEngine.h"

class Vector2;
class DX_API Matrix2
{
public:
	Matrix2();
	Matrix2(const Vector2&, const Vector2&);
	Matrix2(float m11, float m12, float m21, float m22);

	bool operator == (const Matrix2&) const;
	bool operator != (const Matrix2&) const;

	Matrix2 operator * (float f) const;
	Matrix2& operator *= (float f);

	Matrix2 operator + (const Matrix2&) const;
	Matrix2 operator - (const Matrix2&) const;
	Matrix2 operator * (const Matrix2&) const;

	Matrix2& operator += (const Matrix2&);
	Matrix2& operator -= (const Matrix2&);
	Matrix2& operator *= (const Matrix2&);

	Matrix2 TransposeMatrix() const;
	Matrix2 InverseMatrix() const;
	float Determinant() const;

public:
	union {
		struct {
			float _11, _12;
			float _21, _22;
		};
		struct {
			float m[2][2];
		};
		float value[4];
	};
};