#pragma once
#include "../Venus.h"

namespace Venus
{
	class VE_API VECommandList
	{
	public:
		VECommandList() = default;
		virtual ~VECommandList() noexcept = default;
	};
}