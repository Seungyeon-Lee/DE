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

		VETextureDescriptor textureDesc;
		textureDesc.type = VETexture::Type2D;
		textureDesc.format = VEPixelFormat::RGBA8Unorm;
		textureDesc.width = 4; // texture minimum size.
		textureDesc.height = 4; // texture minimum size.
		textureDesc.depth = 1;
		textureDesc.mipmapLevelCount = 1;
		textureDesc.sampleCount = 1;
		textureDesc.usage = VETexture::UsageShaderRead;
		texture = graphicsDevice->CreateTexture(textureDesc);
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
	VEObject<VETexture> texture;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
