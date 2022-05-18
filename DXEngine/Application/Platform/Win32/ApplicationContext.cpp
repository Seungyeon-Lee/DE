#if defined(_WIN32)
#include "ApplicationContext.h"
#include <Windows.h>

int ApplicationContext::MessageLoop()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
		}
	}

	return (int)msg.wParam;
}

#endif