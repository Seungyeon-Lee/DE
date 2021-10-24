#pragma once
#include "DXEngine.h"

class Vector3;
class DX_API Matrix3
{
public:
	Matrix3();
	Matrix3(const Vector3& row1, const Vector3& row2, const Vector3& row3);
	Matrix3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33);

	bool operator == (const Matrix3& m) const;
	bool operator != (const Matrix3& m) const;

	Matrix3 operator * (float f) const;
	Matrix3& operator *= (float f);

	Matrix3 operator + (const Matrix3& m) const;
	Matrix3 operator - (const Matrix3& m) const;
	Matrix3 operator * (const Matrix3& m) const;

	Matrix3& operator += (const Matrix3& m);
	Matrix3& operator -= (const Matrix3& m);
	Matrix3& operator *= (const Matrix3& m);

	Matrix3 TransposeMatrix() const;
	Matrix3 InverseMatrix() const;
	float Determinant() const;

public:
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		struct {
			float m[3][3];
		};
		float value[9];
	};
};