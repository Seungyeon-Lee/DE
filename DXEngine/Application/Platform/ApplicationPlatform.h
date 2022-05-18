#pragma once
#include "../VEApplicationContextInterface.h"

#include "Win32/ApplicationContext.h"

VEApplicationContextInterface* CreateApplicationContext()
{
	return new ApplicationContext();
}