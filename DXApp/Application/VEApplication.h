#pragma once
#include "Venus.h"
#include "VEInclude.h"
#include "Scene/VEScene.h"
#include <thread>

using namespace Venus;

namespace VenusApp
{
	class VenusApplication final : public Venus::VEApplication
	{
	public:
		VenusApplication();
		~VenusApplication();

	protected:
		void OnInitialize() override;
		void OnTerminate() override;
		void Update();

	private:
		std::jthread loopThread;

		VEObject<VEScene> scene;
	};
}