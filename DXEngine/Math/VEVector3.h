#pragma once
#include "../DXEngine.h"

class VEMatrix3;
class DX_API VEVector3
{
public:
	VEVector3();
	VEVector3(float x, float y, float z);

	static float Dot(const VEVector3&, const VEVector3&);
	static VEVector3 Cross(const VEVector3&, const VEVector3&);

	bool operator == (const VEVector3&) const;
	bool operator != (const VEVector3&) const;

	VEVector3 operator * (float) const;
	VEVector3& operator *= (float);

	VEVector3 operator + (const VEVector3&) const;
	VEVector3 operator - (const VEVector3&) const;
	VEVector3& operator += (const VEVector3&);
	VEVector3& operator -= (const VEVector3&);

	VEVector3 operator * (const VEMatrix3&) const;
	VEVector3& operator *= (const VEMatrix3&);
	VEVector3 operator - () const;

	float Length() const;
	float LengthSq() const;
	VEVector3& Normalize();

public:
	union {
		struct {
			float x, y, z;
		};
		float value[3];
	};
};