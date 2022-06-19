#include "VESize.h"

using namespace Venus;

VESize::VESize() : width(0.0f), height(0.0f) {}

VESize::VESize(float width, float height) : width(width), height(height) {}

VESize::VESize(const class VESize& v) : width(v.width), height(v.height) {}

bool VESize::operator == (const VESize& v) const {
	return ((width == v.width) && (height == v.height));
}

bool VESize::operator != (const VESize& v) const {
	return ((width != v.width) || (height != v.height));
}

VESize VESize::operator * (float f) const {
	return VESize(width * f, height * f);
}

VESize& VESize::operator *= (float f) {
	width *= f;
	height *= f;
	return *this;
}

VESize VESize::operator / (float f) const {
	return VESize(width / f, height / f);
}

VESize& VESize::operator /= (float f) {
	width /= f;
	height /= f;
	return *this;
}


VESize VESize::operator + (const VESize& v) const {
	return VESize(width + v.width, height + v.height);
}

VESize VESize::operator - (const VESize& v) const {
	return VESize(width - v.width, height - v.height);
}

VESize& VESize::operator += (const VESize& v) {
	width += v.width;
	height += v.height;
	return *this;
}

VESize& VESize::operator -= (const VESize& v) {
	width -= v.width;
	height -= v.height;
	return *this;
}
