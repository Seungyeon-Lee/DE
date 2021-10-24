#include "Vector4.h"
#include "Matrix4.h"
#include <math.h>

Vector4::Vector4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
}

Vector4::Vector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w) {
}

float Vector4::Dot(const Vector4& v1, const Vector4& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

bool Vector4::operator == (const Vector4& v) const {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vector4::operator != (const Vector4& v) const {
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

Vector4 Vector4::operator + (const Vector4& v) const {
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

Vector4 Vector4::operator - (const Vector4& v) const {
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

Vector4 Vector4::operator * (const Matrix4& m) const {
	return { x * m._11 + y * m._21 + z * m._31 + w * m._41
		   , x * m._12 + y * m._22 + z * m._32 + w * m._42
		   , x * m._13 + y * m._23 + z * m._33 + w * m._43
		   , x * m._14 + y * m._24 + z * m._34 + w * m._44 };
}

Vector4 Vector4::operator * (float f) const {
	return { x * f, y * f, z * f, w * f };
}

Vector4& Vector4::operator += (const Vector4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator -= (const Vector4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4& Vector4::operator *= (const Matrix4& m) {
	Vector4 v{ *this };
	x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
	y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
	z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
	w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;
	return *this;
}

Vector4& Vector4::operator *= (float f) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

float Vector4::Length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSq() const {
	return x * x + y * y + z * z + w * w;
}

Vector4& Vector4::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
		z *= var;
		w *= var;
	}
	return *this;
}
