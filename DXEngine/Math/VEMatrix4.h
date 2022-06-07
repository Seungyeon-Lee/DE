#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VEVector4;
	class VE_API VEMatrix4
	{
	public:
		VEMatrix4();
		VEMatrix4(const VEVector4& row1, const VEVector4& row2,
			const VEVector4& row3, const VEVector4& row4);
		VEMatrix4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);

		bool operator == (const VEMatrix4& m) const;
		bool operator != (const VEMatrix4& m) const;

		VEMatrix4 operator * (float f) const;
		VEMatrix4& operator *= (float f);

		VEMatrix4 operator + (const VEMatrix4& m) const;
		VEMatrix4 operator - (const VEMatrix4& m) const;
		VEMatrix4 operator * (const VEMatrix4& m) const;

		VEMatrix4& operator += (const VEMatrix4& m);
		VEMatrix4& operator -= (const VEMatrix4& m);
		VEMatrix4& operator *= (const VEMatrix4& m);

		VEMatrix4 TransposeMatrix() const;
		VEMatrix4 InverseMatrix() const;
		float Determinant() const;

	public:
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			struct {
				float m[4][4];
			};
			float value[16];
		};
	};
}