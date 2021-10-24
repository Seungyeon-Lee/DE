#pragma once
#include "DXEngine.h"

class Matrix2;
class DX_API Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(const class Vector2&);

	bool operator == (const Vector2&) const;
	bool operator != (const Vector2&) const;

	static float Dot(const Vector2&, const Vector2&);
	static float Cross(const Vector2&, const Vector2&);

	Vector2 operator + () const;
	Vector2 operator - () const;

	Vector2 operator * (float) const;
	Vector2& operator *= (float);

	Vector2 operator + (const Vector2&) const;
	Vector2 operator - (const Vector2&) const;
	Vector2 operator * (const Matrix2& m) const;
	Vector2& operator += (const Vector2&);
	Vector2& operator -= (const Vector2&);
	Vector2& operator *= (const Matrix2&);

	float Length() const;
	float LengthSq() const;
	Vector2& Normalize();

public:
	union {
		struct {
			float x, y;
		};
		float value[2];
	};
};
