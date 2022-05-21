#include "VEAffineTransform2.h"
#include "VELinearTransform2.h"
#include "VEMatrix3.h"
#include <math.h>

using namespace Venus;

VEAffineTransform2::VEAffineTransform2()
	: matrix2()
	, translation() { }

VEAffineTransform2::VEAffineTransform2(const VEMatrix3& m)
	: matrix2(m._11, m._12,
		m._21, m._22)
	, translation(m._31, m._32) {}

bool VEAffineTransform2::operator == (const VEAffineTransform2& at) const {
	return translation == at.translation && matrix2 == at.matrix2;
}

bool VEAffineTransform2::operator != (const VEAffineTransform2& at) const {
	return translation != at.translation || matrix2 != at.matrix2;
}

VEAffineTransform2& VEAffineTransform2::Translate(float x, float y) {
	translation.x += x;
	translation.y += y;
	return *this;
}

VEAffineTransform2& VEAffineTransform2::Translate(const VEVector2& v) {
	translation.x += v.x;
	translation.y += v.y;
	return *this;
}

VEAffineTransform2& VEAffineTransform2::Multiply(const VELinearTransform2& lt) {
	translation *= lt.matrix2;
	matrix2 *= lt.matrix2;
	return *this;
}

VEAffineTransform2& VEAffineTransform2::Multiply(const VEAffineTransform2& at) {
	// t = v1 * m + v2
	translation = translation * at.matrix2 + at.translation;
	matrix2 *= at.matrix2;
	return *this;
}

VEMatrix3 VEAffineTransform2::Matrix3() const {
	return { matrix2._11, matrix2._12, 0.f
		   , matrix2._21, matrix2._22, 0.f
		   , translation.x, translation.y, 1.f };
}
