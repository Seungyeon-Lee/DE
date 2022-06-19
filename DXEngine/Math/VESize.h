#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VE_API VESize final
	{
	public:
		VESize();
		VESize(float width, float height);
		VESize(const class VESize&);

		bool operator == (const VESize&) const;
		bool operator != (const VESize&) const;

		VESize operator + (const VESize&) const;
		VESize operator - (const VESize&) const;
		VESize operator * (float) const;
		VESize operator / (float) const;

		VESize& operator += (const VESize&);
		VESize& operator -= (const VESize&);
		VESize& operator *= (float);
		VESize& operator /= (float);

		float width;
		float height;
	};
}
