#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VEVector2;
	class VE_API VEMatrix2
	{
	public:
		VEMatrix2();
		VEMatrix2(const VEVector2&, const VEVector2&);
		VEMatrix2(float m11, float m12, float m21, float m22);

		bool operator == (const VEMatrix2&) const;
		bool operator != (const VEMatrix2&) const;

		VEMatrix2 operator * (float f) const;
		VEMatrix2& operator *= (float f);

		VEMatrix2 operator + (const VEMatrix2&) const;
		VEMatrix2 operator - (const VEMatrix2&) const;
		VEMatrix2 operator * (const VEMatrix2&) const;

		VEMatrix2& operator += (const VEMatrix2&);
		VEMatrix2& operator -= (const VEMatrix2&);
		VEMatrix2& operator *= (const VEMatrix2&);

		VEMatrix2 TransposeMatrix() const;
		VEMatrix2 InverseMatrix() const;
		float Determinant() const;

	public:
		union {
			struct {
				float _11, _12;
				float _21, _22;
			};
			struct {
				float m[2][2];
			};
			float value[4];
		};
	};
}