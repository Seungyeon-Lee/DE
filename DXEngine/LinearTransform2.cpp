#include "LinearTransform2.h"
#include "Vector2.h"
#include <math.h>

LinearTransform2::LinearTransform2()
	: matrix2() {}

LinearTransform2::LinearTransform2(const DX_API::Matrix2& m)
	: matrix2(m) {}

bool LinearTransform2::operator == (const LinearTransform2& lt) const {
	return matrix2 == lt.matrix2;
}

bool LinearTransform2::operator != (const LinearTransform2& lt) const {
	return matrix2 != lt.matrix2;
}

LinearTransform2& LinearTransform2::Scale(float x, float y) {
	matrix2._11 *= x;
	matrix2._12 *= y;
	matrix2._21 *= x;
	matrix2._22 *= y;
	return *this;
}

LinearTransform2& LinearTransform2::Scale(const Vector2& v) {
	matrix2._11 *= v.x;
	matrix2._12 *= v.y;
	matrix2._21 *= v.x;
	matrix2._22 *= v.y;
	return *this;
}

LinearTransform2& LinearTransform2::Rotate(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	matrix2 *= DX_API::Matrix2{ cos, sin, -sin, cos };
	return *this;
}

LinearTransform2& LinearTransform2::Multiply(const DX_API::Matrix2& m) {
	matrix2 *= m;
	return *this;
}
