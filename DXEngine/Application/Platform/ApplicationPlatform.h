#pragma once
#include "../VEApplicationContextInterface.h"
#include "Win32/ApplicationContext.h"

Venus::VEApplicationContextInterface* CreateApplicationContext()
{
	return new Venus::ApplicationContext();
}