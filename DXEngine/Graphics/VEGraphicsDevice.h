#pragma once
#include "../Venus.h"
#include "VECommandQueue.h"
#include "VECommandList.h"

namespace Venus
{
	class VE_API VEGraphicsDevice
	{
	public:
		virtual ~VEGraphicsDevice() noexcept = default;

		virtual VECommandQueue* CreateCommandQueue() = 0;
		virtual VECommandList* CreateCommandList() = 0;

		static VEGraphicsDevice* CreateGraphicsDevice();

	protected:
		// User에게 상속을 허용하지 않는다.
		VEGraphicsDevice() = default;
	};
}