#include "gtest/gtest.h"
#include "Venus.h"

using namespace Venus;

struct Constants
{
	VEMatrix4 worldViewProj;
};

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

		renderPipeline = graphicsDevice->CreateRenderPipeline(/*descriptor*/);

		camera.SetupViewMatrix(VEVector3{ 0.f, 0.f, -5.f }, VEVector3{}, VEVector3{ 0.f, 1.f, 0.f });
		camera.SetPerspective(0.25f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);

		Constants constants;
		constants.worldViewProj = camera.ViewMatrix() * camera.ProjectionMatrix();

		// Update the constant buffer with the latest worldViewProj matrix.
		constantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(Constants), VEGPUBuffer::CPUCacheMode::UPLOAD);
		constantsBuffer->WriteData(&constants, sizeof(Constants));

		loopThread = std::jthread([this](std::stop_token token)
		{
			while (!token.stop_requested())
			{
				Update();
				Draw();
			}
		});
	}

	void OnTerminate() override
	{
		loopThread.request_stop();
		loopThread.join();
	}

	void Update()
	{

	}

	void Draw()
	{
		if (VEObject<VECommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
		{
			if (VEObject<VERenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
			{
				VEViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
				encoder->SetViewport(viewport);

				VERect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
				encoder->SetScissorRect(scissorRect);

				encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), VELinearColor::green);
				encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), VERenderCommandEncoder::DepthStencilClearFlag::All, 1.f, 0);

				encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

				encoder->EndEncoding();
			}

			commandBuffer->Commit();
		}

		swapChain->Present();
		commandQueue->WaitComplete();
	}

private:
	std::jthread loopThread;

	VEObject<VEWindow> window;
	VEObject<VEGraphicsDevice> graphicsDevice;
	VEObject<VECommandQueue> commandQueue;
	VEObject<VESwapChain> swapChain;
	VEObject<VERenderPipeline> renderPipeline;

	VEObject<VEGPUBuffer> vertexBuffer;
	VEObject<VETexture> texture;

	VECamera camera;
	VEObject<VEGPUBuffer> constantsBuffer;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
