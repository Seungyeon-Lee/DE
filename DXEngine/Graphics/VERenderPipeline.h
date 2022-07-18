#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VEShader.h"
#include "VEBlendState.h"
#include "VEPixelFormat.h"
#include "VEVertexDescriptor.h"

namespace Venus
{
	class VE_API VERenderPipeline : public VERefCounter
	{
	public:
		VERenderPipeline() = default;
		virtual ~VERenderPipeline() noexcept = default;
	};

	enum class VEPrimitiveTopologyType
	{
		Point,
		Line,
		Triangle
	};

	struct VERenderPipelineColorAttachmentDescriptor
	{
		VEPixelFormat pixelFormat;

		bool blendingEnabled;

		VEBlendOperation alphaBlendOperation;
		VEBlendFactor sourceAlphaBlendFactor;
		VEBlendFactor destinationAlphaBlendFactor;

		VEBlendOperation rgbBlendOperation;
		VEBlendFactor sourceRGBBlendFactor;
		VEBlendFactor destinationRGBBlendFactor;

		VEColorWriteMask writeMask = VEColorWriteMask::ColorWriteMaskAll;
	};

	struct VERenderPipelineDescriptor
	{
		uint32_t sampleCount;
		VEObject<VEShader> vertexShader;
		VEObject<VEShader> fragmentShader;

		VEVertexDescriptor vertexDescriptor;
		std::vector<VERenderPipelineColorAttachmentDescriptor> colorAttachments;
		VEPixelFormat depthStencilAttachmentPixelFormat;

		VEPrimitiveTopologyType inputPrimitiveTopology;
	};
}