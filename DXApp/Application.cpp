#include "Common/DXApp.h"

class Application : public DXApp
{
public:
    Application(HINSTANCE hInstance);
	~Application();

	virtual bool Initialize()override;

private:
    virtual void Update()override;
    virtual void Draw()override;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    try
    {
        Application theApp(hInstance);
        if(!theApp.Initialize())
            return 0;

        return theApp.Run();
    }
    catch(DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }
}

Application::Application(HINSTANCE hInstance)
: DXApp(hInstance)
{
}

Application::~Application()
{
}

bool Application::Initialize()
{
    if(!DXApp::Initialize())
		return false;
		
	return true;
}

void Application::Update()
{

}

void Application::Draw()
{
 
}
