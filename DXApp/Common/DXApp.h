#pragma once
#include <vector>
#include "Venus.h"
#include "tiny_obj_loader.h"

using namespace std;
using namespace Venus;

class DXApp : public VEApplication
{
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

public:
    DXApp();
    virtual ~DXApp();
	void OnInitialize() override;
	void OnTerminate() override;
	void Update();
	void Draw();
	void LoadTestModel();

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

