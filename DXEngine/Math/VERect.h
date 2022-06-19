#pragma once
#include "../VEInclude.h"
#include "VEPoint.h"
#include "VESize.h"

namespace Venus
{
	class VE_API VERect
	{
	public:
		VERect();
		VERect(VEPoint leftTop, VESize size);
		VERect(float x, float y, float width, float height);

        bool Intersect(const VERect& rect) const;
        bool IsInside(const VERect& rect) const;
        bool IsInside(const VEPoint& point) const;

        VEPoint LeftTop() const;
        VEPoint RightTop() const;
        VEPoint LeftBottom() const;
        VEPoint RightBottom() const;

        union
        {
            struct
            {
                VEPoint leftTop;
                VESize size;
            };
            struct
            {
                float x, y;
                float width, height;
            };
        };
	};
}
