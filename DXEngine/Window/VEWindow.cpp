#include "VEWindow.h"
#include "Platform/WindowPlatform.h"

VEWindow* VEWindow::CreatePlatformWindow()
{
	return Platform::CreatePlatformWindow();
}
