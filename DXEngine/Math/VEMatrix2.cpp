#include "VEMatrix2.h"
#include "VEVector2.h"

using namespace Venus;

VEMatrix2::VEMatrix2()
	: _11(1.0f), _12(0.0f)
	, _21(0.0f), _22(1.0f) { }

VEMatrix2::VEMatrix2(const VEVector2& r1, const VEVector2& r2)
	: _11(r1.x), _12(r1.y)
	, _21(r2.x), _22(r2.y) { }

VEMatrix2::VEMatrix2(float m11, float m12, float m21, float m22)
	: _11(m11), _12(m12)
	, _21(m21), _22(m22) { }

bool VEMatrix2::operator == (const VEMatrix2& m) const {
	return _11 == m._11 && _12 == m._12
		&& _21 == m._21 && _22 == m._22;
}

bool VEMatrix2::operator != (const VEMatrix2& m) const {
	return _11 != m._11 || _12 != m._12
		|| _21 != m._21 || _22 != m._22;
}

VEMatrix2 VEMatrix2::operator * (float f) const {
	return { (_11 * f), (_12 * f)
		   , (_21 * f), (_22 * f) };
}

VEMatrix2& VEMatrix2::operator *= (float f) {
	_11 *= f;
	_12 *= f;
	_21 *= f;
	_22 *= f;
	return *this;
}

VEMatrix2 VEMatrix2::operator + (const VEMatrix2& m) const {
	return { _11 + m._11, _12 + m._12
		   , _21 + m._21, _22 + m._22 };
}

VEMatrix2 VEMatrix2::operator - (const VEMatrix2& m) const {
	return { _11 - m._11, _12 - m._12
		   , _21 - m._21, _22 - m._22 };
}

VEMatrix2 VEMatrix2::operator * (const VEMatrix2& m) const {
	return { (_11 * m._11 + _12 * m._21), (_11 * m._12 + _12 * m._22)
		   , (_21 * m._11 + _22 * m._21), (_21 * m._12 + _22 * m._22) };
}

VEMatrix2& VEMatrix2::operator += (const VEMatrix2& m) {
	_11 += m._11;
	_12 += m._12;
	_21 += m._21;
	_22 += m._22;
	return *this;
}

VEMatrix2& VEMatrix2::operator -= (const VEMatrix2& m) {
	_11 -= m._11;
	_12 -= m._12;
	_21 -= m._21;
	_22 -= m._22;
	return *this;
}

VEMatrix2& VEMatrix2::operator *= (const VEMatrix2& m) {
	VEMatrix2 mat{ *this };
	_11 = (mat._11 * m._11) + (mat._12 * m._21);
	_12 = (mat._11 * m._12) + (mat._12 * m._22);
	_21 = (mat._21 * m._11) + (mat._22 * m._21);
	_22 = (mat._21 * m._12) + (mat._22 * m._22);
	return *this;
}

VEMatrix2 VEMatrix2::TransposeMatrix() const {
	return { _11, _21
		   , _12, _22 };
}

VEMatrix2 VEMatrix2::InverseMatrix() const {
	float determinant = Determinant();
	// invertible matrix
	if (determinant != 0.0f) {
		// adjoint matrix / determinant
		float detInv = 1.0f / determinant;
		return { _22 * detInv, -_12 * detInv
			   , -_21 * detInv, _11 * detInv };
	}
	// singular matrix
	else {
		return {};
	}
}

float VEMatrix2::Determinant() const {
	return _11 * _22 - _12 * _21;
}
