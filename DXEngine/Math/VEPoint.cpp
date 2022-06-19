#include "VEPoint.h"

using namespace Venus;

VEPoint::VEPoint() : x(0.0f), y(0.0f) {}

VEPoint::VEPoint(float x, float y) : x(x), y(y) {}

VEPoint::VEPoint(const class VEPoint& v) : x(v.x), y(v.y) {}

bool VEPoint::operator == (const VEPoint& v) const {
	return ((x == v.x) && (y == v.y));
}

bool VEPoint::operator != (const VEPoint& v) const {
	return ((x != v.x) || (y != v.y));
}

VEPoint VEPoint::operator + () const {
	return VEPoint(+x, +y);
}

VEPoint VEPoint::operator - () const {
	return VEPoint(-x, -y);
}

VEPoint VEPoint::operator * (float f) const {
	return VEPoint(x * f, y * f);
}

VEPoint& VEPoint::operator *= (float f) {
	x *= f;
	y *= f;
	return *this;
}

VEPoint VEPoint::operator + (const VEPoint& v) const {
	return VEPoint(x + v.x, y + v.y);
}

VEPoint VEPoint::operator - (const VEPoint& v) const {
	return VEPoint(x - v.x, y - v.y);
}

VEPoint& VEPoint::operator += (const VEPoint& v) {
	x += v.x;
	y += v.y;
	return *this;
}

VEPoint& VEPoint::operator -= (const VEPoint& v) {
	x -= v.x;
	y -= v.y;
	return *this;
}
