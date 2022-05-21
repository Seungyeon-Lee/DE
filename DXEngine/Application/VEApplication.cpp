#include "VEApplication.h"
#include "Platform/ApplicationPlatform.h"

using namespace Venus;

VEApplication::VEApplication()
	:context(nullptr)
{
	context = CreateApplicationContext();
}

VEApplication::~VEApplication()
{
	delete context;
	context = nullptr;
}

int VEApplication::Run()
{
	OnInitialize();

	int code = context->MessageLoop();

	OnTerminate();
	return code;
}