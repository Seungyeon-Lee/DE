#include "gtest/gtest.h"
#include <vector>
#include "Venus.h"
#include "tiny_obj_loader.h"

using namespace Venus;

struct Vertex
{
	VEVector3 pos;
	VEVector3 normal;
	VELinearColor color;
};

struct StaticMesh
{
	std::vector <Vertex> vertices;
	VEObject<VEGPUBuffer> vertexBuffer;
};

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

		vertexShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimpleShader.hlsl", "VS", VEShader::StageType::Vertex);
		pixelShader = graphicsDevice->CreateShader(L"Resource/Shaders/SimpleShader.hlsl", "PS", VEShader::StageType::Fragment);

		VERenderPipelineDescriptor descriptor{};
		descriptor.sampleCount = 1;
		descriptor.vertexShader = vertexShader;
		descriptor.fragmentShader = pixelShader;
		descriptor.vertexDescriptor.attributes = {
			{VEVertexFormat::Float3, "POSITION", 0, 0},
			{VEVertexFormat::Float3, "NORMAL", 0, 12 },
			{VEVertexFormat::Float4, "COLOR", 0, 24 },
		};
		descriptor.colorAttachments = { { VEPixelFormat::RGBA8Unorm, false } };
		descriptor.depthStencilAttachmentPixelFormat = VEPixelFormat::Depth24UnormStencil8;
		descriptor.inputPrimitiveTopology = VEPrimitiveTopologyType::Triangle;

		renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);

		camera.SetupViewMatrix(VEVector3{ 0.f, 0.f, -4.5f }, VEVector3{ }, VEVector3{ 0.f, 1.f, 0.f });
		camera.SetPerspective(0.3f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);

		Constants constants;
		constants.worldViewProj = camera.ViewMatrix() * camera.ProjectionMatrix();

		// Update the constant buffer with the latest worldViewProj matrix.
		constantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(Constants), VEGPUBuffer::CPUCacheMode::UPLOAD);
		constantsBuffer->WriteData(&constants, sizeof(Constants));

		LoadTestModel();

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

				encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), VELinearColor::violet);
				encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), VERenderCommandEncoder::DepthStencilClearFlag::All, 0.f, 0);

				encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

				encoder->SetConstantBuffer(0, constantsBuffer);

				for (const StaticMesh& mesh : staticMeshes)
				{
					encoder->SetVertexBuffer(mesh.vertexBuffer, sizeof(Vertex));

					encoder->DrawPrimitives(VERenderCommandEncoder::PrimitiveType::Triangle,
						(uint32_t)mesh.vertices.size(), 1, 0, 0);
				}

				encoder->EndEncoding();
			}

			commandBuffer->Commit();
		}

		swapChain->Present();
		commandQueue->WaitComplete();
	}

	void LoadTestModel()
	{
		tinyobj::ObjReader reader;
		if (!reader.ParseFromFile("Resource/Meshes/bunny.obj"))
		{
			EXPECT_EQ(0, 1);
		}

		auto& attrib = reader.GetAttrib();
		auto& shapes = reader.GetShapes();
		auto& materials = reader.GetMaterials();

		// Loop over shapes
		for (size_t i = 0; i < shapes.size(); ++i)
		{
			std::vector<Vertex> vertices;
			vertices.reserve(shapes[i].mesh.num_face_vertices.size() * 3);

			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); ++j)
			{
				size_t fv = size_t(shapes[i].mesh.num_face_vertices[j]);

				// Loop over vertices in the face.
				for (size_t k = 0; k < fv; ++k)
				{
					Vertex vertex{};

					tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + k];

					// access to vertex
					vertex.pos = VEVector3(attrib.vertices[3 * size_t(idx.vertex_index) + 0],
						attrib.vertices[3 * size_t(idx.vertex_index) + 1],
						attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

					// Check if `normal_index` is zero or positive. negative = no normal data
					if (idx.normal_index >= 0) {
						vertex.normal = VEVector3(attrib.normals[3 * size_t(idx.normal_index) + 0],
							attrib.normals[3 * size_t(idx.normal_index) + 1],
							attrib.normals[3 * size_t(idx.normal_index) + 2]);
					}

					// Check if `texcoord_index` is zero or positive. negative = no texcoord data
					/*if (idx.texcoord_index >= 0) {
						tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					}*/

					// Optional: vertex colors
					vertex.color = VELinearColor(attrib.colors[3 * size_t(idx.vertex_index) + 0],
						attrib.colors[3 * size_t(idx.vertex_index) + 1],
						attrib.colors[3 * size_t(idx.vertex_index) + 2],
						1.f);

					vertices.push_back(vertex);
				}
				index_offset += fv;
			}

			VEObject<VEGPUBuffer> vertexBuffer = graphicsDevice->CreateGPUBuffer(vertices.size() * sizeof(VEGPUBuffer), VEGPUBuffer::CPUCacheMode::UPLOAD);
			vertexBuffer->WriteData(vertices.data(), vertices.size() * sizeof(VEGPUBuffer));
			staticMeshes.emplace_back(std::move(vertices), vertexBuffer);
		}
	}

private:
	std::jthread loopThread;

	VEObject<VEWindow> window;
	VEObject<VEGraphicsDevice> graphicsDevice;
	VEObject<VECommandQueue> commandQueue;
	VEObject<VESwapChain> swapChain;
	VEObject<VERenderPipeline> renderPipeline;

	VEObject<VETexture> texture;

	VEObject<VEShader> vertexShader;
	VEObject<VEShader> pixelShader;

	VECamera camera;
	std::vector<StaticMesh> staticMeshes;
	VEObject<VEGPUBuffer> constantsBuffer;
};

TEST(Application, Init)
{
	TestApplication app;
	app.Run();
}
