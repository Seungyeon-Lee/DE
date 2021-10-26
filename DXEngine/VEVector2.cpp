#include "VEVector2.h"
#include "VEMatrix2.h"
#include <math.h>

VEVector2::VEVector2() : x(0.0f), y(0.0f) {}

VEVector2::VEVector2(float x, float y) : x(x), y(y) {}

VEVector2::VEVector2(const class VEVector2& v) : x(v.x), y(v.y) {}

float VEVector2::Dot(const VEVector2& v1, const VEVector2& v2) {
	return (v1.x * v2.x) + (v1.y * v2.y);
}

float VEVector2::Cross(const VEVector2& v1, const VEVector2& v2) {
	return (v1.x * v2.y) - (v1.y * v2.y);
}

bool VEVector2::operator == (const VEVector2& v) const {
	return ((x == v.x) && (y == v.y));
}

bool VEVector2::operator != (const VEVector2& v) const {
	return ((x != v.x) || (y != v.y));
}

VEVector2 VEVector2::operator + () const {
	return VEVector2(+x, +y);
}

VEVector2 VEVector2::operator - () const {
	return VEVector2(-x, -y);
}

VEVector2 VEVector2::operator * (float f) const {
	return VEVector2(x * f, y * f);
}

VEVector2& VEVector2::operator *= (float f) {
	x *= f;
	y *= f;
	return *this;
}

VEVector2 VEVector2::operator + (const VEVector2& v) const {
	return VEVector2(x + v.x, y + v.y);
}

VEVector2 VEVector2::operator - (const VEVector2& v) const {
	return VEVector2(x - v.x, y - v.y);
}

VEVector2 VEVector2::operator * (const VEMatrix2& m) const {
	return { (x * m._11 + y * m._21)
		   , (x * m._12 + y * m._22) };
}

VEVector2& VEVector2::operator += (const VEVector2& v) {
	x += v.x;
	y += v.y;
	return *this;
}

VEVector2& VEVector2::operator -= (const VEVector2& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}

VEVector2& VEVector2::operator *= (const VEMatrix2& m)
{
	VEVector2 v(*this);
	x = v.x * m._11 + v.y * m._21;
	y = v.x * m._12 + v.y * m._22;
	return *this;
}

float VEVector2::Length() const {
	return sqrtf(x * x + y * y);
}

float VEVector2::LengthSq() const {
	return (x * x + y * y);
}

VEVector2& VEVector2::Normalize() {
	if (LengthSq() > 0.0f) {
		float var = 1.0f / Length();
		x *= var;
		y *= var;
	}
	return *this;
}
