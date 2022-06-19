#include "VERect.h"

using namespace Venus;

VERect::VERect() : x(0.f), y(0.f), width(0.f), height(0.f) {}
VERect::VERect(VEPoint leftTop, VESize size) : x(leftTop.x), y(leftTop.y), width(size.width), height(size.height) {}
VERect::VERect(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

bool VERect::Intersect(const VERect& r) const
{
	VEPoint rb = RightBottom();
	VEPoint compareRb = r.RightBottom();
	return x <= compareRb.x && r.x <= rb.x && y <= compareRb.y && r.y <= rb.y;
}
bool VERect::IsInside(const VERect& r) const
{
	return x <= r.x && y <= r.y && width >= r.width && height >= r.height;
}
bool VERect::IsInside(const VEPoint& p) const
{
	VEPoint rb = RightBottom();
	return x <= p.x && y <= p.y && rb.x >= p.x && rb.y >= p.y;
}

VEPoint VERect::LeftTop() const
{
	return { x, y };
}
VEPoint VERect::RightTop() const
{
	return { x + width, y };
}
VEPoint VERect::LeftBottom() const
{
	return { x, y + height };
}
VEPoint VERect::RightBottom() const
{
	return { x + width, y + height };
}