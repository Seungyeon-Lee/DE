#include "VELinearTransform2.h"
#include "VEVector2.h"
#include <math.h>

using namespace Venus;

VELinearTransform2::VELinearTransform2()
	: matrix2() {}

VELinearTransform2::VELinearTransform2(const VEMatrix2& m)
	: matrix2(m) {}

bool VELinearTransform2::operator == (const VELinearTransform2& lt) const {
	return matrix2 == lt.matrix2;
}

bool VELinearTransform2::operator != (const VELinearTransform2& lt) const {
	return matrix2 != lt.matrix2;
}

VELinearTransform2& VELinearTransform2::Scale(float x, float y) {
	matrix2._11 *= x;
	matrix2._12 *= y;
	matrix2._21 *= x;
	matrix2._22 *= y;
	return *this;
}

VELinearTransform2& VELinearTransform2::Scale(const VEVector2& v) {
	matrix2._11 *= v.x;
	matrix2._12 *= v.y;
	matrix2._21 *= v.x;
	matrix2._22 *= v.y;
	return *this;
}

VELinearTransform2& VELinearTransform2::Rotate(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	matrix2 *= VEMatrix2{ cos, sin, -sin, cos };
	return *this;
}

VELinearTransform2& VELinearTransform2::Multiply(const VEMatrix2& m) {
	matrix2 *= m;
	return *this;
}
