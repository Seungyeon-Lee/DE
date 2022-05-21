#pragma once
#if defined(_WIN32)
#include "../../../Venus.h"
#include "../../VEApplicationContextInterface.h"

namespace Venus
{
	class ApplicationContext : public VEApplicationContextInterface
	{
	public:
		ApplicationContext() = default;
		~ApplicationContext() = default;

		int MessageLoop() override;
	};
}
#endif