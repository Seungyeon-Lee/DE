#include "VEScene.h"
#include "tiny_obj_loader.h"

using namespace VenusApp;

VEScene::VEScene()
{
}

VEScene::~VEScene()
{
}

void VEScene::Initialize()
{
	window = VEWindow::CreatePlatformWindow();
	window->Create();
	window->Show();

	graphicsDevice = VEGraphicsDevice::CreateGraphicsDevice();
	commandQueue = graphicsDevice->CreateCommandQueue();
	swapChain = commandQueue->CreateSwapChain(window);

	CreateWhiteTexture();

	camera.SetPerspective(0.25f * 3.1415926535f, window->AspectRatio(), 1.0f, 1000.f);

	BuildConstantsBuffers();
	BuildRenderPipeline();

	models.push_back(LoadModel("Resource/Meshes/bunny.obj"));
}

void VEScene::Terminate()
{
}

void VEScene::Update()
{
	UpdateCamera();
	UpdateMainPassConstants();
}

void VEScene::Draw()
{
	if (VEObject<VECommandBuffer> commandBuffer = commandQueue->CreateCommandBuffer())
	{
		if (VEObject<VERenderCommandEncoder> encoder = commandBuffer->CreateRenderCommandEncoder(renderPipeline))
		{
			VEViewport viewport(0, 0, (float)window->Width(), (float)window->Height(), 0.f, 1.f);
			encoder->SetViewport(viewport);

			VERect scissorRect(0, 0, (float)window->Width(), (float)window->Height());
			encoder->SetScissorRect(scissorRect);

			encoder->ClearRenderTargetView(swapChain->CurrentColorTexture(), VELinearColor::black);
			encoder->ClearDepthStencilView(swapChain->DepthStencilTexture(), VERenderCommandEncoder::DepthStencilClearFlag::All, 0.f, 0);

			encoder->SetRenderTargets({ swapChain->CurrentColorTexture() }, swapChain->DepthStencilTexture());

			encoder->SetConstantBuffer(2, mainPassConstantsBuffer);

			for (const VEModel& model : models)
			{
				UpdateObjectConstants(model);
				UpdateMaterialConstants(model);

				encoder->SetConstantBuffer(0, objectConstantsBuffer);
				encoder->SetConstantBuffer(1, materialConstantsBuffer);

				for (const VEMesh& mesh : model.meshes)
				{
					encoder->SetVertexBuffer(mesh.vertexBuffer, sizeof(VEVertex));
					encoder->DrawPrimitives(VERenderCommandEncoder::PrimitiveType::Triangle,
						(uint32_t)mesh.vertices.size(), 1, 0, 0);
				}
			}

			encoder->EndEncoding();
		}

		commandBuffer->Commit();
	}

	swapChain->Present();
	commandQueue->WaitComplete();
}

void VEScene::CreateWhiteTexture()
{
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

void VEScene::BuildConstantsBuffers()
{
	mainPassConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(VenusMainPassConstants), VEGPUBuffer::CPUCacheMode::UPLOAD);
	objectConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(VenusObjectConstants), VEGPUBuffer::CPUCacheMode::UPLOAD);
	materialConstantsBuffer = graphicsDevice->CreateGPUBuffer(sizeof(VenusMaterialConstants), VEGPUBuffer::CPUCacheMode::UPLOAD);
}

void VEScene::BuildRenderPipeline()
{
	VERenderPipelineDescriptor descriptor{};
	descriptor.sampleCount = 1;
	descriptor.vertexShader = graphicsDevice->CreateShader(L"Resource/Shaders/Default.hlsl", "VS", VEShader::StageType::Vertex);
	descriptor.fragmentShader = graphicsDevice->CreateShader(L"Resource/Shaders/Default.hlsl", "PS", VEShader::StageType::Fragment);
	descriptor.vertexDescriptor.attributes = {
		{VEVertexFormat::Float3, "POSITION", 0, 0},
		{VEVertexFormat::Float3, "NORMAL", 0, 12 },
		{VEVertexFormat::Float4, "COLOR", 0, 24 },
		{VEVertexFormat::Float2, "TEXCOORD", 0, 40 }
	};
	descriptor.colorAttachments = { { VEPixelFormat::RGBA8Unorm, false } };
	descriptor.depthStencilAttachmentPixelFormat = VEPixelFormat::Depth24UnormStencil8;
	descriptor.inputPrimitiveTopology = VEPrimitiveTopologyType::Triangle;

	renderPipeline = graphicsDevice->CreateRenderPipeline(descriptor);
}

void VEScene::UpdateCamera()
{
	camera.SetupViewMatrix(VEVector3{ 0.f, 0.f, -4.5f }, VEVector3{ }, VEVector3{ 0.f, 1.f, 0.f });
}

void VEScene::UpdateMainPassConstants()
{
	auto viewMat = camera.ViewMatrix();
	auto projectionMat = camera.ProjectionMatrix();

	// HLSL is column-major matrix.
	VenusMainPassConstants mainPassConstants;
	mainPassConstants.view = viewMat.TransposeMatrix();
	mainPassConstants.invView = viewMat.InverseMatrix().TransposeMatrix();
	mainPassConstants.proj = projectionMat.TransposeMatrix();
	mainPassConstants.invProj = projectionMat.InverseMatrix().TransposeMatrix();
	mainPassConstants.viewProj = (viewMat * projectionMat).TransposeMatrix();
	mainPassConstants.invViewProj = (viewMat * projectionMat).InverseMatrix().TransposeMatrix();

	mainPassConstants.eyePosW = camera.Position();
	mainPassConstants.renderTargetSize = VEVector2((float)window->Width(), (float)window->Height());
	mainPassConstants.invRenderTargetSize = VEVector2(1.f / window->Width(), 1.f / window->Height());
	mainPassConstants.nearZ = camera.NearZ();
	mainPassConstants.farZ = camera.FarZ();
	mainPassConstants.ambientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	mainPassConstants.lights[0].direction = { 0.57735f, -0.57735f, 0.57735f };
	mainPassConstants.lights[0].strength = { 0.6f, 0.6f, 0.6f };
	mainPassConstants.lights[1].direction = { -0.57735f, -0.57735f, 0.57735f };
	mainPassConstants.lights[1].strength = { 0.3f, 0.3f, 0.3f };
	mainPassConstants.lights[2].direction = { 0.0f, -0.707f, -0.707f };
	mainPassConstants.lights[2].strength = { 0.15f, 0.15f, 0.15f };

	mainPassConstantsBuffer->WriteData(&mainPassConstants, sizeof(VenusMainPassConstants));
}

void VEScene::UpdateObjectConstants(const VEModel& model)
{
	VenusObjectConstants objConstants;
	objConstants.world = model.world.TransposeMatrix();
	objConstants.texTransform = model.texTransform.TransposeMatrix();

	objectConstantsBuffer->WriteData(&objConstants, sizeof(VenusObjectConstants));
}

void VEScene::UpdateMaterialConstants(const VEModel& model)
{
	VenusMaterialConstants matConstants;
	matConstants.diffuseAlbedo = model.material.diffuseAlbedo;
	matConstants.fresnelR0 = model.material.fresnelR0;
	matConstants.roughness = model.material.roughness;
	matConstants.matTransform = model.texTransform;

	materialConstantsBuffer->WriteData(&matConstants, sizeof(VenusMaterialConstants));
}

VEModel VEScene::LoadModel(const std::string& path)
{
	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile(std::string(path)))
	{
		if (!reader.Error().empty())
		{
			// TODO: Error 贸府
		}
	}

	if (!reader.Warning().empty())
	{
		// TODO: Error 贸府
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	VEModel newModel{};
	newModel.material.diffuseAlbedo = VELinearColor(1.f, 1.f, 1.f, 1.f);
	newModel.material.fresnelR0 = VEVector3(0.05f, 0.05f, 0.05f);
	newModel.material.roughness = 0.3f;

	// Loop over shapes
	for (size_t i = 0; i < shapes.size(); ++i)
	{
		std::vector<VEVertex> vertices;
		vertices.reserve(shapes[i].mesh.num_face_vertices.size() * 3);

		// Loop over faces(polygon)
		size_t index_offset = 0;
		for (size_t j = 0; j < shapes[i].mesh.num_face_vertices.size(); ++j)
		{
			size_t fv = size_t(shapes[i].mesh.num_face_vertices[j]);

			// Loop over vertices in the face.
			for (size_t k = 0; k < fv; ++k)
			{
				VEVertex vertex{};

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

		VEObject<VEGPUBuffer> vertexBuffer = graphicsDevice->CreateGPUBuffer(vertices.size() * sizeof(VEVertex), VEGPUBuffer::CPUCacheMode::UPLOAD);
		vertexBuffer->WriteData(vertices.data(), vertices.size() * sizeof(VEVertex));
		newModel.meshes.emplace_back(std::move(vertices), vertexBuffer);
	}

	return newModel;
}
