#pragma once
#include "../VEInclude.h"
#include "../Math/VEVector3.h"
#include "../Math/VEMatrix4.h" 

namespace Venus
{
	class VE_API VECamera final
	{
	public:
		VECamera();
		~VECamera() = default;

		void SetupViewMatrix(const VEVector3& pos, const VEVector3& targetPos, const VEVector3& worldUpDir);

		void SetPerspective(float fov, float aspect, float near, float far);

		float NearZ() const { return near; }
		float FarZ() const { return far; }
		VEVector3 Position() const { return position; }
		VEMatrix4 ViewMatrix() const { return viewMatrix; }
		VEMatrix4 ProjectionMatrix() const { return projectionMatrix; }

	private:
		float near;
		float far;
		VEVector3 position;
		VEMatrix4 viewMatrix;
		VEMatrix4 projectionMatrix;
	};
}