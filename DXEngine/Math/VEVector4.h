#pragma once
#include "../Venus.h"

namespace Venus
{
	class VEMatrix4;
	class VE_API VEVector4
	{
	public:
		VEVector4();
		VEVector4(float x, float y, float z, float w);

		static float Dot(const VEVector4& v1, const VEVector4& v2);

		bool operator == (const VEVector4& v) const;
		bool operator != (const VEVector4& v) const;

		VEVector4 operator * (float f) const;
		VEVector4& operator *= (float f);

		VEVector4 operator + (const VEVector4& v) const;
		VEVector4 operator - (const VEVector4& v) const;
		VEVector4 operator * (const VEMatrix4& m) const;

		VEVector4& operator += (const VEVector4& v);
		VEVector4& operator -= (const VEVector4& v);
		VEVector4& operator *= (const VEMatrix4& m);

		float Length() const;
		float LengthSq() const;
		VEVector4& Normalize();

	public:
		union {
			struct {
				float x, y, z, w;
			};
			float value[4];
		};
	};
}