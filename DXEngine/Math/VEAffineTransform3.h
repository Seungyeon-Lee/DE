#pragma once
#include "../DXEngine.h"
#include "VEMatrix3.h"
#include "VEVector3.h"

class VEMatrix4;
class VELinearTransform3;
class DX_API VEAffineTransform3
{
public:
	VEAffineTransform3();
	VEAffineTransform3(const VEMatrix4& m);

	bool operator == (const VEAffineTransform3& at) const;
	bool operator != (const VEAffineTransform3& at) const;

	VEAffineTransform3& Translate(float x, float y, float z);
	VEAffineTransform3& Translate(const VEVector3& v);
	VEAffineTransform3& Multiply(const VELinearTransform3& lt);
	VEAffineTransform3& Multiply(const VEAffineTransform3& at);

	VEMatrix4 Matrix4() const;
	const VEMatrix3& Matrix3() const { return matrix3; }

public:
	VEMatrix3 matrix3;
	VEVector3 translation;
};