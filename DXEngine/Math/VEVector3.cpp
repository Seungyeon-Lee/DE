#include "VEVector3.h"
#include "VEMatrix3.h"
#include <math.h>

using namespace Venus;

VEVector3::VEVector3() : x(0.0f), y(0.0f), z(0.0f) { }

VEVector3::VEVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }

float VEVector3::Dot(const VEVector3& v1, const VEVector3& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

VEVector3 VEVector3::Cross(const VEVector3& v1, const VEVector3& v2) {
	return { v1.y * v2.z - v1.z * v2.y
		   , v1.z * v2.x - v1.x * v2.z
		   , v1.x * v2.y - v1.y * v2.x };
}

bool VEVector3::operator == (const VEVector3& v) const {
	return x == v.x && y == v.y && z == v.z;
}

bool VEVector3::operator != (const VEVector3& v) const {
	return x != v.x || y != v.y || z != v.z;
}

VEVector3 VEVector3::operator + (const VEVector3& v) const {
	return { x + v.x, y + v.y, z + v.z };
}

VEVector3 VEVector3::operator - (const VEVector3& v) const {
	return { x - v.x, y - v.y, z - v.z };
}

VEVector3 VEVector3::operator * (const VEMatrix3& m) const {
	return { x * m._11 + y * m._21 + z * m._31
		   , x * m._12 + y * m._22 + z * m._32
		   , x * m._13 + y * m._23 + z * m._33 };
}

VEVector3 VEVector3::operator * (float f) const {
	return { x * f, y * f, z * f };
}

VEVector3& VEVector3::operator += (const VEVector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

VEVector3& VEVector3::operator -= (const VEVector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

VEVector3& VEVector3::operator *= (const VEMatrix3& m) {
	VEVector3 v{ *this };
	x = v.x * m._11 + v.y * m._21 + v.z * m._31;
	y = v.x * m._12 + v.y * m._22 + v.z * m._32;
	z = v.x * m._13 + v.y * m._23 + v.z * m._33;
	return *this;
}

VEVector3& VEVector3::operator *= (float f) {
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

VEVector3 VEVector3::operator - () const {
	return { -x, -y, -z };
}


float VEVector3::Length() const {
	return sqrtf(x * x + y * y + z * z);
}

float VEVector3::LengthSq() const {
	return x * x + y * y + z * z;
}

VEVector3& VEVector3::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
		z *= var;
	}
	return *this;
}
