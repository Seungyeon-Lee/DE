#include "gtest/gtest.h"
#include "Venus.h"

using namespace Venus;

class TestApplication : public VEApplication
{
public:
	TestApplication()
		: window(nullptr)
		, graphicsDevice(nullptr)
	{}

	void OnInitialize() override
	{
		window = VEWindow::CreatePlatformWindow();
		window->Create();
		window->Show();

		graphicsDevice = VEGraphicsDevice::CreateGraphicsDevice();
		commandQueue = graphicsDevice->CreateCommandQueue();
		commandList = graphicsDevice->CreateCommandList();
		swapChain = commandQueue->CreateSwapChain(window);

		vertexBuffer = graphicsDevice->CreateGPUBuffer(50000, VEGPUBuffer::CPUCacheMode::UPLOAD);
	}

	void OnTerminate() override
	{
	}

private:
	VEObject<VEWindow> window;
	VEObject<VEGraphicsDevice> graphicsDevice;
	VEObject<VECommandQueue> commandQueue;
	VEObject<VECommandList> commandList;
	VEObject<VESwapChain> swapChain;
	VEObject<VEGPUBuffer> vertexBuffer;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
