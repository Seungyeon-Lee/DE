#include "Vector2.h"
#include "Matrix2.h"
#include <math.h>

Vector2::Vector2() : x(0.0f), y(0.0f) {}

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2(const class Vector2& v) : x(v.x), y(v.y) {}

float Vector2::Dot(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float Vector2::Cross(const Vector2& v1, const Vector2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.y);
}

bool Vector2::operator == (const Vector2& v) const {
	return ((x == v.x) && (y == v.y));
}

bool Vector2::operator != (const Vector2& v) const {
	return ((x != v.x) || (y != v.y));
}

Vector2 Vector2::operator + () const {
	return Vector2(+x, +y);
}

Vector2 Vector2::operator - () const {
	return Vector2(-x, -y);
}

Vector2 Vector2::operator * (float f) const {
	return Vector2(x * f, y * f);
}

Vector2& Vector2::operator *= (float f) {
	x *= f;
	y *= f;
	return *this;
}

Vector2 Vector2::operator + (const Vector2& v) const {
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator - (const Vector2& v) const {
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator * (const Matrix2& m) const {
	return { (x * m._11 + y * m._21)
		   , (x * m._12 + y * m._22) };
}

Vector2& Vector2::operator += (const Vector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2& Vector2::operator *= (const Matrix2& m)
{
	Vector2 v(*this);
	x = v.x * m._11 + v.y * m._21;
	y = v.x * m._12 + v.y * m._22;
	return *this;
}

float Vector2::Length() const {
	return sqrtf(x * x + y * y);
}

float Vector2::LengthSq() const {
	return (x * x + y * y);
}

Vector2& Vector2::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
	}
	return *this;
}
