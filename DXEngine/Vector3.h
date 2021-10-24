#pragma once
#include "DXEngine.h"

class Matrix3;
class DX_API Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	static float Dot(const Vector3&, const Vector3&);
	static Vector3 Cross(const Vector3&, const Vector3&);

	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;

	Vector3 operator * (float) const;
	Vector3& operator *= (float);

	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3& operator += (const Vector3&);
	Vector3& operator -= (const Vector3&);

	Vector3 operator * (const Matrix3&) const;
	Vector3& operator *= (const Matrix3&);

	float Length() const;
	float LengthSq() const;
	Vector3& Normalize();

public:
	union {
		struct {
			float x, y, z;
		};
		float value[3];
	};
};