#include "AffineTransform2.h"
#include "LinearTransform2.h"
#include "Matrix3.h"
#include <math.h>

AffineTransform2::AffineTransform2()
	: matrix2()
	, translation() { }

AffineTransform2::AffineTransform2(const DX_API::Matrix3& m)
	: matrix2(m._11, m._12,
		m._21, m._22)
	, translation(m._31, m._32) {}

bool AffineTransform2::operator == (const AffineTransform2& at) const {
	return translation == at.translation && matrix2 == at.matrix2;
}

bool AffineTransform2::operator != (const AffineTransform2& at) const {
	return translation != at.translation || matrix2 != at.matrix2;
}

AffineTransform2& AffineTransform2::Translate(float x, float y) {
	translation.x += x;
	translation.y += y;
	return *this;
}

AffineTransform2& AffineTransform2::Translate(const Vector2& v) {
	translation.x += v.x;
	translation.y += v.y;
	return *this;
}

AffineTransform2& AffineTransform2::Multiply(const LinearTransform2& lt) {
	translation *= lt.matrix2;
	matrix2 *= lt.matrix2;
	return *this;
}

AffineTransform2& AffineTransform2::Multiply(const AffineTransform2& at) {
	// t = v1 * m + v2
	translation = translation * at.matrix2 + at.translation;
	matrix2 *= at.matrix2;
	return *this;
}

Matrix3 AffineTransform2::Matrix3() const {
	return { matrix2._11, matrix2._12, 0.f
		   , matrix2._21, matrix2._22, 0.f
		   , translation.x, translation.y, 1.f };
}
