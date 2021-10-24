#include "Matrix2.h"
#include "Vector2.h"

Matrix2::Matrix2()
	: _11(1.0f), _12(0.0f)
	, _21(0.0f), _22(1.0f) { }

Matrix2::Matrix2(const Vector2& r1, const Vector2& r2)
	: _11(r1.x), _12(r1.y)
	, _21(r2.x), _22(r2.y) { }

Matrix2::Matrix2(float m11, float m12, float m21, float m22)
	: _11(m11), _12(m12)
	, _21(m21), _22(m22) { }

bool Matrix2::operator == (const Matrix2& m) const {
	return _11 == m._11 && _12 == m._12
		&& _21 == m._21 && _22 == m._22;
}

bool Matrix2::operator != (const Matrix2& m) const {
	return _11 != m._11 || _12 != m._12
		|| _21 != m._21 || _22 != m._22;
}

Matrix2 Matrix2::operator * (float f) const {
	return { (_11 * f), (_12 * f)
		   , (_21 * f), (_22 * f) };
}

Matrix2& Matrix2::operator *= (float f) {
	_11 *= f;
	_12 *= f;
	_21 *= f;
	_22 *= f;
	return *this;
}

Matrix2 Matrix2::operator + (const Matrix2& m) const {
	return { _11 + m._11, _12 + m._12
		   , _21 + m._21, _22 + m._22 };
}

Matrix2 Matrix2::operator - (const Matrix2& m) const {
	return { _11 - m._11, _12 - m._12
		   , _21 - m._21, _22 - m._22 };
}

Matrix2 Matrix2::operator * (const Matrix2& m) const {
	return { (_11 * m._11 + _12 * m._21), (_11 * m._12 + _12 * m._22)
		   , (_21 * m._11 + _22 * m._21), (_21 * m._12 + _22 * m._22) };
}

Matrix2& Matrix2::operator += (const Matrix2& m) {
	_11 += m._11;
	_12 += m._12;
	_21 += m._21;
	_22 += m._22;
	return *this;
}

Matrix2& Matrix2::operator -= (const Matrix2& m) {
	_11 -= m._11;
	_12 -= m._12;
	_21 -= m._21;
	_22 -= m._22;
	return *this;
}

Matrix2& Matrix2::operator *= (const Matrix2& m) {
	Matrix2 mat{ *this };
	_11 = (mat._11 * m._11) + (mat._12 * m._21);
	_12 = (mat._11 * m._12) + (mat._12 * m._22);
	_21 = (mat._21 * m._11) + (mat._22 * m._21);
	_22 = (mat._21 * m._12) + (mat._22 * m._22);
	return *this;
}

Matrix2 Matrix2::TransposeMatrix() const {
	return { _11, _21
		   , _12, _22 };
}

Matrix2 Matrix2::InverseMatrix() const {
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

float Matrix2::Determinant() const {
	return _11 * _22 - _12 * _21;
}
