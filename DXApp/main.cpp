#include <Windows.h>
#include "Application/VEApplication.h"

int WINAPI wWinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ PWSTR cmdLine, _In_ int cmdShow)
{
	VenusApp::VenusApplication app;
	return app.Run();
}