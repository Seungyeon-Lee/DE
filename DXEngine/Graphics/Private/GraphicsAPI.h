#pragma once
#include "../VEGraphicsDevice.h"

namespace Venus::Private
{
#if defined(_WIN32)
	namespace Direct3D
	{
		VEGraphicsDevice* CreateGraphicsDevice();
	}
#endif

	VEGraphicsDevice* CreateGraphicsDevice()
	{
		return Direct3D::CreateGraphicsDevice();
	}
}