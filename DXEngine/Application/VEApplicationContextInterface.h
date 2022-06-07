#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VE_API VEApplicationContextInterface
	{
	public:
		VEApplicationContextInterface() = default;
		virtual ~VEApplicationContextInterface() = default;

		virtual int MessageLoop() = 0;
	};
}