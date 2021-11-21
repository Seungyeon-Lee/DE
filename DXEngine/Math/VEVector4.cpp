#include "VEVector4.h"
#include "VEMatrix4.h"
#include <math.h>

VEVector4::VEVector4()
	: x(0.0f), y(0.0f), z(0.0f), w(0.0f) {
}

VEVector4::VEVector4(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w) {
}

float VEVector4::Dot(const VEVector4& v1, const VEVector4& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

bool VEVector4::operator == (const VEVector4& v) const {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool VEVector4::operator != (const VEVector4& v) const {
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

VEVector4 VEVector4::operator + (const VEVector4& v) const {
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

VEVector4 VEVector4::operator - (const VEVector4& v) const {
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

VEVector4 VEVector4::operator * (const VEMatrix4& m) const {
	return { x * m._11 + y * m._21 + z * m._31 + w * m._41
		   , x * m._12 + y * m._22 + z * m._32 + w * m._42
		   , x * m._13 + y * m._23 + z * m._33 + w * m._43
		   , x * m._14 + y * m._24 + z * m._34 + w * m._44 };
}

VEVector4 VEVector4::operator * (float f) const {
	return { x * f, y * f, z * f, w * f };
}

VEVector4& VEVector4::operator += (const VEVector4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

VEVector4& VEVector4::operator -= (const VEVector4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

VEVector4& VEVector4::operator *= (const VEMatrix4& m) {
	VEVector4 v{ *this };
	x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
	y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
	z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
	w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;
	return *this;
}

VEVector4& VEVector4::operator *= (float f) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

float VEVector4::Length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float VEVector4::LengthSq() const {
	return x * x + y * y + z * z + w * w;
}

VEVector4& VEVector4::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
		z *= var;
		w *= var;
	}
	return *this;
}
