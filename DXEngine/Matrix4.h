#pragma once
#include "DXEngine.h"

class Vector4;
class DX_API Matrix4
{
public:
	Matrix4();
	Matrix4(const Vector4& row1, const Vector4& row2,
		const Vector4& row3, const Vector4& row4);
	Matrix4(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	bool operator == (const Matrix4& m) const;
	bool operator != (const Matrix4& m) const;

	Matrix4 operator * (float f) const;
	Matrix4& operator *= (float f);

	Matrix4 operator + (const Matrix4& m) const;
	Matrix4 operator - (const Matrix4& m) const;
	Matrix4 operator * (const Matrix4& m) const;

	Matrix4& operator += (const Matrix4& m);
	Matrix4& operator -= (const Matrix4& m);
	Matrix4& operator *= (const Matrix4& m);

	Matrix4 TransposeMatrix() const;
	Matrix4 InverseMatrix() const;
	float Determinant() const;

public:
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		struct {
			float m[4][4];
		};
		float value[16];
	};
};