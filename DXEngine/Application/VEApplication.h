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
		// User�� ���� platform�� �����ؼ� ����ϵ��� �����.
		VEApplicationContextInterface* context;
	};
}

