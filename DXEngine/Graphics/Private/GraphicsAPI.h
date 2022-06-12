#pragma once
#include "../VEGraphicsDevice.h"

namespace Venus::Private
{
#if defined(_WIN32)
	namespace Direct3D12
	{
		VEGraphicsDevice* CreateGraphicsDevice();
	}
#endif

	VEGraphicsDevice* CreateGraphicsDevice()
	{
		return Direct3D12::CreateGraphicsDevice();
	}
}