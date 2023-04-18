#pragma once
#include "Venus.h"
#include "VEInclude.h"
#include "Rendering/VELight.h"
#include "Rendering/VEModel.h"

using namespace Venus;

namespace VenusApp
{
	enum { MaxLights = 16 };

	struct VenusObjectConstants
	{
		VEMatrix4 world;
		VEMatrix4 texTransform;
	};

	struct VenusMainPassConstants
	{
		VEMatrix4 view;
		VEMatrix4 invView;
		VEMatrix4 proj;
		VEMatrix4 invProj;
		VEMatrix4 viewProj;
		VEMatrix4 invViewProj;
		VEVector3 eyePosW;
		float cbPerObjectPad1 = 0.0f;
		VEVector2 renderTargetSize;
		VEVector2 invRenderTargetSize;
		float nearZ;
		float farZ;
		VEVector2 pad2;
		VELinearColor ambientLight = { 0.f, 0.f, 0.f, 1.f };

		VELight lights[MaxLights];
	};

	struct VenusMaterialConstants
	{
		VELinearColor diffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
		VEVector3 fresnelR0 = { 0.01f, 0.01f, 0.01f };
		float roughness = 0.25f;

		// Used in texture mapping.
		VEMatrix4 matTransform = {};
	};

	class VEScene final : public VERefCounter
	{
	public:
		VEScene();
		~VEScene();

		void Initialize();
		void Terminate();
		void Update();
		void Draw();

	private:
		void CreateWhiteTexture();
		void BuildConstantsBuffers();
		void BuildRenderPipeline();

		void UpdateCamera();
		void UpdateMainPassConstants();
		void UpdateObjectConstants(const VEModel& renderItem);
		void UpdateMaterialConstants(const VEModel& renderItem);

		VEModel LoadModel(const std::string& path);

		VECamera camera;
		std::vector<VEModel> models;

		VEObject<VERenderPipeline> renderPipeline;
		VEObject<VEGPUBuffer> mainPassConstantsBuffer;
		VEObject<VEGPUBuffer> objectConstantsBuffer;
		VEObject<VEGPUBuffer> materialConstantsBuffer;

	private:
		VEObject<VEWindow> window;
		VEObject<VESwapChain> swapChain;

		VEObject<VECommandQueue> commandQueue;
		VEObject<VEGraphicsDevice> graphicsDevice;

		VEObject<VETexture> texture;
	};
}