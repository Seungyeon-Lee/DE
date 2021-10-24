#include "Vector3.h"
#include "Matrix3.h"
#include <math.h>

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) { }

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2) {
	return { v1.y * v2.z - v1.z * v2.y
		   , v1.z * v2.x - v1.x * v2.z
		   , v1.x * v2.y - v1.y * v2.x };
}

bool Vector3::operator == (const Vector3& v) const {
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator != (const Vector3& v) const {
	return x != v.x || y != v.y || z != v.z;
}

Vector3 Vector3::operator + (const Vector3& v) const {
	return { x + v.x, y + v.y, z + v.z };
}

Vector3 Vector3::operator - (const Vector3& v) const {
	return { x - v.x, y - v.y, z - v.z };
}

Vector3 Vector3::operator * (const Matrix3& m) const {
	return { x * m._11 + y * m._21 + z * m._31
		   , x * m._12 + y * m._22 + z * m._32
		   , x * m._13 + y * m._23 + z * m._33 };
}

Vector3 Vector3::operator * (float f) const {
	return { x * f, y * f, z * f };
}

Vector3& Vector3::operator += (const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3& Vector3::operator *= (const Matrix3& m) {
	Vector3 v{ *this };
	x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	z = v.x * m._13 + v.y * m._23 + v.z * m._33;
	return *this;
}

Vector3& Vector3::operator *= (float f) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

float Vector3::Length() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSq() const {
	return x * x + y * y + z * z;
}

Vector3& Vector3::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
		z *= var;
	}
	return *this;
}
