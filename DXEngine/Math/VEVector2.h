#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VEMatrix2;
	class VE_API VEVector2
	{
	public:
		VEVector2();
		VEVector2(float x, float y);
		VEVector2(const class VEVector2&);

		bool operator == (const VEVector2&) const;
		bool operator != (const VEVector2&) const;

		static float Dot(const VEVector2&, const VEVector2&);
		static float Cross(const VEVector2&, const VEVector2&);

		VEVector2 operator + () const;
		VEVector2 operator - () const;

		VEVector2 operator * (float) const;
		VEVector2& operator *= (float);

		VEVector2 operator + (const VEVector2&) const;
		VEVector2 operator - (const VEVector2&) const;
		VEVector2 operator * (const VEMatrix2& m) const;
		VEVector2& operator += (const VEVector2&);
		VEVector2& operator -= (const VEVector2&);
		VEVector2& operator *= (const VEMatrix2&);

		float Length() const;
		float LengthSq() const;
		VEVector2& Normalize();

	public:
		union {
			struct {
				float x, y;
			};
			float value[2];
		};
	};
}