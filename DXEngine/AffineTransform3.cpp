#include "AffineTransform3.h"
#include "LinearTransform3.h"
#include "Matrix4.h"
#include <math.h>

AffineTransform3::AffineTransform3()
	: matrix3()
	, translation() {}

AffineTransform3::AffineTransform3(const DX_API::Matrix4& m)
	: matrix3(m._11, m._12, m._13,
		m._21, m._22, m._23,
		m._31, m._32, m._33)
	, translation(m._41, m._42, m._43) {}

bool AffineTransform3::operator == (const AffineTransform3& at) const {
	return translation == at.translation && matrix3 == at.matrix3;
}

bool AffineTransform3::operator != (const AffineTransform3& at) const {
	return translation != at.translation || matrix3 != at.matrix3;;
}

AffineTransform3& AffineTransform3::Translate(float x, float y, float z) {
	translation.x += x;
	translation.y += y;
	translation.z += z;
	return *this;
}

AffineTransform3& AffineTransform3::Translate(const Vector3& v) {
	translation.x += v.x;
	translation.y += v.y;
	translation.z += v.z;
	return *this;
}

AffineTransform3& AffineTransform3::Multiply(const LinearTransform3& lt) {
	translation *= lt.matrix3;
	matrix3 *= lt.matrix3;
	return *this;
}

AffineTransform3& AffineTransform3::Multiply(const AffineTransform3& at) {
	translation = translation * at.matrix3 + at.translation;
	matrix3 *= at.matrix3;
	return *this;
}

Matrix4 AffineTransform3::Matrix4() const {
	return { matrix3._11, matrix3._12, matrix3._13, 0.f
		   , matrix3._21, matrix3._22, matrix3._23, 0.f
		   , matrix3._31, matrix3._32, matrix3._33, 0.f
		   , translation.x, translation.y, translation.z, 1.f };
}
