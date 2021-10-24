#pragma once
#include "DXEngine.h"

class Matrix4;
class DX_API Vector4
{
public:
	Vector4();
	Vector4(float x, float y, float z, float w);

	static float Dot(const Vector4& v1, const Vector4& v2);

	bool operator == (const Vector4& v) const;
	bool operator != (const Vector4& v) const;

	Vector4 operator * (float f) const;
	Vector4& operator *= (float f);

	Vector4 operator + (const Vector4& v) const;
	Vector4 operator - (const Vector4& v) const;
	Vector4 operator * (const Matrix4& m) const;

	Vector4& operator += (const Vector4& v);
	Vector4& operator -= (const Vector4& v);
	Vector4& operator *= (const Matrix4& m);

	float Length() const;
	float LengthSq() const;
	Vector4& Normalize();

public:
	union {
		struct {
			float x, y, z, w;
		};
		float value[4];
	};
};