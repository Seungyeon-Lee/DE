#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VE_API VEPoint
	{
	public:
		VEPoint();
		VEPoint(float x, float y);
		VEPoint(const class VEPoint&);

		bool operator == (const VEPoint&) const;
		bool operator != (const VEPoint&) const;

		VEPoint operator + () const;
		VEPoint operator - () const;

		VEPoint operator * (float) const;
		VEPoint& operator *= (float);

		VEPoint operator + (const VEPoint&) const;
		VEPoint operator - (const VEPoint&) const;
		VEPoint& operator += (const VEPoint&);
		VEPoint& operator -= (const VEPoint&);

	public:
		union {
			struct {
				float x, y;
			};
			float value[2];
		};
	};
}