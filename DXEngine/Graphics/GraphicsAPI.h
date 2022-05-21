#pragma once
#include "VEGraphicsDevice.h"

namespace Venus::GraphicsAPI
{
#if defined(_WIN32)
	namespace Direct3D
	{
		VEGraphicsDevice* CreateGraphicsDevice();
	}
#endif

	VEGraphicsDevice* CreateGraphicsDevice()
	{
#if defined(_WIN32)
		return Direct3D::CreateGraphicsDevice();
#else
		class Dummy : public VEGraphicsDevice { };
		return new Dummy();
#endif
	}
}