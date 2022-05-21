#include "VELinearTransform3.h"
#include "VEVector3.h"
#include <math.h>

using namespace Venus;

VELinearTransform3::VELinearTransform3()
	: matrix3() {}

VELinearTransform3::VELinearTransform3(const VEMatrix3& m)
	: matrix3(m) {}

bool VELinearTransform3::operator==(const VELinearTransform3& lt) const {
	return matrix3 == lt.matrix3;
}

bool VELinearTransform3::operator!=(const VELinearTransform3& lt) const {
	return matrix3 != lt.matrix3;
}

VELinearTransform3& VELinearTransform3::Scale(float x, float y, float z) {
	matrix3._11 *= x;
	matrix3._12 *= y;
	matrix3._13 *= z;
	matrix3._21 *= x;
	matrix3._22 *= y;
	matrix3._23 *= z;
	matrix3._31 *= x;
	matrix3._32 *= y;
	matrix3._33 *= z;
	return *this;
}

VELinearTransform3& VELinearTransform3::Scale(const VEVector3& v) {
	matrix3._11 *= v.x;
	matrix3._12 *= v.y;
	matrix3._13 *= v.z;
	matrix3._21 *= v.x;
	matrix3._22 *= v.y;
	matrix3._23 *= v.z;
	matrix3._31 *= v.x;
	matrix3._32 *= v.y;
	matrix3._33 *= v.z;
	return *this;
}

VELinearTransform3& VELinearTransform3::RotateX(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	matrix3 *= VEMatrix3(1.f, 0.f, 0.f,
		0.f, cos, -sin,
		0.f, sin, cos);
	return *this;

}

VELinearTransform3& VELinearTransform3::RotateY(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	matrix3 *= VEMatrix3{ cos, 0.f, sin,
						  0.f, 1.f, 0.f,
						  -sin, 0.f, cos };
	return *this;
}

VELinearTransform3& VELinearTransform3::RotateZ(float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	matrix3 *= VEMatrix3{ cos, -sin, 0.f,
						  sin, cos, 0.f,
						  0.f, 0.f, 1.f };
	return *this;
}

VELinearTransform3& VELinearTransform3::Rotate(const VEVector3& axis, float angle) {
	float cos = cosf(angle);
	float sin = sinf(angle);
	float revCos = 1.f - cos;
	matrix3 *= VEMatrix3{ cos + revCos * (axis.x * axis.x),
						  revCos * (axis.x * axis.y) + (sin * axis.z),
						  revCos * (axis.x * axis.z) - (sin * axis.y),
						  revCos * (axis.x * axis.y) - (sin * axis.z),
						  cos + revCos * (axis.y * axis.y),
						  revCos * (axis.y * axis.z) + (sin * axis.x),
						  revCos * (axis.x * axis.z) + (sin * axis.y),
						  revCos * (axis.y * axis.z) - (sin * axis.x),
						  cos + revCos * (axis.z * axis.z) };
	return *this;
}

VELinearTransform3& VELinearTransform3::Multiply(const VEMatrix3& m) {
	matrix3 *= m;
	return *this;
}
