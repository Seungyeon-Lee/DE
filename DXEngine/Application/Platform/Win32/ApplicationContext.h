#pragma once
#if defined(_WIN32)
#include "../../../DXEngine.h"
#include "../../VEApplicationContextInterface.h"

class ApplicationContext : public VEApplicationContextInterface
{
public:
	ApplicationContext() = default;
	~ApplicationContext() = default;

	int MessageLoop() override;
};
#endif