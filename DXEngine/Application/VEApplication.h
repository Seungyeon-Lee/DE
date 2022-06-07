#pragma once
#include "../VEInclude.h"
#include "VEApplicationContextInterface.h"

namespace Venus
{
	class VE_API VEApplication
	{
	public:
		VEApplication();
		virtual ~VEApplication();

		int Run();

	protected:
		virtual void OnInitialize() = 0;
		virtual void OnTerminate() = 0;

	private:
		// User가 따로 platform을 정의해서 사용하도록 만든다.
		VEApplicationContextInterface* context;
	};
}

