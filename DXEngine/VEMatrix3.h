#pragma once
#include "DXEngine.h"

class VEVector3;
class DX_API VEMatrix3
{
public:
	VEMatrix3();
	VEMatrix3(const VEVector3& row1, const VEVector3& row2, const VEVector3& row3);
	VEMatrix3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33);

	bool operator == (const VEMatrix3& m) const;
	bool operator != (const VEMatrix3& m) const;

	VEMatrix3 operator * (float f) const;
	VEMatrix3& operator *= (float f);

	VEMatrix3 operator + (const VEMatrix3& m) const;
	VEMatrix3 operator - (const VEMatrix3& m) const;
	VEMatrix3 operator * (const VEMatrix3& m) const;

	VEMatrix3& operator += (const VEMatrix3& m);
	VEMatrix3& operator -= (const VEMatrix3& m);
	VEMatrix3& operator *= (const VEMatrix3& m);

	VEMatrix3 TransposeMatrix() const;
	VEMatrix3 InverseMatrix() const;
	float Determinant() const;

public:
	union {
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
		struct {
			float m[3][3];
		};
		float value[9];
	};
};