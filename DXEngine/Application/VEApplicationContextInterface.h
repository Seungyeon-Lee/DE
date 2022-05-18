#pragma once
#include "../DXEngine.h"

class DX_API VEApplicationContextInterface
{
public:
	VEApplicationContextInterface() = default;
	virtual ~VEApplicationContextInterface() = default;

	virtual int MessageLoop() = 0;
};