#include "VEApplication.h"

using namespace VenusApp;

VenusApplication::VenusApplication()
	: scene(nullptr)
{
	scene = new VEScene();
}

VenusApplication::~VenusApplication()
{
}


void VenusApplication::OnInitialize()
{
	scene->Initialize();

	loopThread = std::jthread([this](std::stop_token token)
	{
		while (!token.stop_requested())
		{
			Update();
		}
	});
}

void VenusApplication::OnTerminate()
{
	loopThread.request_stop();
	loopThread.join();

	scene->Terminate();
}

void VenusApplication::Update()
{
	scene->Update();
	scene->Draw();
}
