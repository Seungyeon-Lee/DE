#include "VEWindow.h"
#include "Platform/WindowPlatform.h"

using namespace Venus;

VEWindow* VEWindow::CreatePlatformWindow()
{
	return Platform::CreatePlatformWindow();
}
