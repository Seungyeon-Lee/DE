#pragma once
#include "../DXEngine.h"
#include "VEApplicationContextInterface.h"

class DX_API VEApplication
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

