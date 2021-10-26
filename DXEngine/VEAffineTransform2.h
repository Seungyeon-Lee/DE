#pragma once
#include "DXEngine.h"
#include "VEMatrix2.h"
#include "VEVector2.h"

class VEMatrix3;
class VELinearTransform2;
class DX_API VEAffineTransform2
{
public:
	VEAffineTransform2();
	VEAffineTransform2(const VEMatrix3& m);

	bool operator == (const VEAffineTransform2& at) const;
	bool operator != (const VEAffineTransform2& at) const;

	VEAffineTransform2& Translate(float x, float y);
	VEAffineTransform2& Translate(const VEVector2& v);
	VEAffineTransform2& Multiply(const VELinearTransform2& lt);
	VEAffineTransform2& Multiply(const VEAffineTransform2& at);

	VEMatrix3 Matrix3() const;
	const VEMatrix2& Matrix2() const { return matrix2; }

public:
	VEMatrix2 matrix2;
	VEVector2 translation;
};