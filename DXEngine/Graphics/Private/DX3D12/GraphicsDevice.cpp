#include "GraphicsDevice.h"
#include "CommandQueue.h"
#include "GPUBuffer.h"
#include "Texture.h"
#include "Type.h"
#include "Shader.h"
#include "RenderPipeline.h"
#include <array>

namespace Venus::Private::Direct3D12
{
	VEGraphicsDevice* CreateGraphicsDevice()
	{
		return new GraphicsDevice();
	}
}

using namespace Venus;
using namespace Venus::Private::Direct3D12;

namespace Private
{
	static std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers()
	{
		// Applications usually only need a handful of samplers.  So just define them all up front
		// and keep them available as part of the root signature.  

		const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
			0, // shaderRegister
			D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

		const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
			1, // shaderRegister
			D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

		const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
			2, // shaderRegister
			D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

		const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
			3, // shaderRegister
			D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

		const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
			4, // shaderRegister
			D3D12_FILTER_ANISOTROPIC, // filter
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
			0.0f,                             // mipLODBias
			8);                               // maxAnisotropy

		const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
			5, // shaderRegister
			D3D12_FILTER_ANISOTROPIC, // filter
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
			D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
			0.0f,                              // mipLODBias
			8);                                // maxAnisotropy

		return {
			pointWrap, pointClamp,
			linearWrap, linearClamp,
			anisotropicWrap, anisotropicClamp };
	}
}

GraphicsDevice::GraphicsDevice()
{
	HRESULT hardwareResult = S_OK;
	// 먼저 Factory를 만든다. 넘버링이 올라갈 수록 기능을 더 제공해준다.
	hardwareResult = CreateDXGIFactory1(IID_PPV_ARGS(&factory));

	// 그래픽 카드에 대한 정보들을 loop 돈다. (책 코드에는 loop 사용 없이 가장 첫 번째 그래픽 카드로 설정)
	// Try to create hardware device.
	hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_12_0,
		IID_PPV_ARGS(&device));

	// Fallback to WARP device.
	if (FAILED(hardwareResult))
	{
		IDXGIAdapter* pWarpAdapter;

		// 그래픽 카드가 없는 경우 CPU로 GPU처럼 행동하게 만들어준다.
		hardwareResult = factory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));

		hardwareResult = D3D12CreateDevice(
			pWarpAdapter,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&device));
	}
}

VEObject<VECommandQueue> GraphicsDevice::CreateCommandQueue()
{
	ComPtr<ID3D12CommandQueue> queue;
	{
		D3D12_COMMAND_QUEUE_DESC desc{};
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		ThrowIfFailed(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue)));
	}
	ComPtr<ID3D12Fence> fence;
	{
		ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));
	}

	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ThrowIfFailed(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator)));

	ComPtr<ID3D12GraphicsCommandList> commandList;
	ThrowIfFailed(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList)));
	commandList->Close();

	return new CommandQueue(this, queue.Get(), commandAllocator.Get(), commandList.Get(), fence.Get());
}

// Ref. DX12 : CreateDefaultBuffer Function
VEObject<VEGPUBuffer> GraphicsDevice::CreateGPUBuffer(size_t size, VEGPUBuffer::CPUCacheMode mode)
{
	D3D12_HEAP_PROPERTIES heapProperty{};
	D3D12_RESOURCE_STATES initialResourceState{};
	switch (mode)
	{
	case GPUBuffer::CPUCacheMode::DEFAULT:
		heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		initialResourceState = D3D12_RESOURCE_STATE_COMMON;
		break;
	case GPUBuffer::CPUCacheMode::UPLOAD:
		heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		initialResourceState = D3D12_RESOURCE_STATE_GENERIC_READ;
		break;
	case GPUBuffer::CPUCacheMode::READBACK:
		heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
		initialResourceState = D3D12_RESOURCE_STATE_COPY_DEST;
		break;
	}

	D3D12_RESOURCE_DESC bufferDesc;
	bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	bufferDesc.Alignment = 0;
	bufferDesc.Width = AlignGPUBufferSize(size);
	bufferDesc.Height = 1;
	bufferDesc.DepthOrArraySize = 1;
	bufferDesc.MipLevels = 1;
	bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
	bufferDesc.SampleDesc.Count = 1;
	bufferDesc.SampleDesc.Quality = 0;
	bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	ComPtr<ID3D12Resource> buffer;
	ThrowIfFailed(device->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&bufferDesc,
		initialResourceState,
		nullptr,
		IID_PPV_ARGS(buffer.GetAddressOf())));

	return new GPUBuffer(buffer.Get(), mode, initialResourceState);
}

// Ref. DX12 : DDSTextureLoader.cpp
VEObject<VETexture> GraphicsDevice::CreateTexture(const VETextureDescriptor& desc)
{
	D3D12_RESOURCE_DESC bufferDesc{};
	bufferDesc.Width = desc.width;
	bufferDesc.Height = desc.height;
	bufferDesc.DepthOrArraySize = desc.depth;
	bufferDesc.MipLevels = desc.mipmapLevelCount;
	bufferDesc.SampleDesc.Count = desc.sampleCount;
	bufferDesc.SampleDesc.Quality = 0;
	bufferDesc.Format = PixelFormat(desc.format);

	switch (desc.type)
	{
	case Texture::Type1D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D; break;
	case Texture::Type2D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D; break;
	case Texture::Type3D: bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D; break;
	}

	D3D12_RESOURCE_STATES initialState = D3D12_RESOURCE_STATE_COMMON;

	// 최적화 방식. 순서대로 체크한다.
	// TODO : 방식에 대한 원리에 대해서는 조금 더 찾아봐야할 듯.
	// default - allow bind shader.
	bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	if (desc.usage & Texture::UsageShaderRead)
	{
		initialState = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE | D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	}
	else
	{
		// for optimize.
		bufferDesc.Flags |= D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
	}
	if (desc.usage & Texture::UsageRenderTarget)
	{
		bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		initialState = D3D12_RESOURCE_STATE_RENDER_TARGET;
	}
	if (desc.usage & Texture::UsageDepthStencil)
	{
		bufferDesc.Flags |= D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
		initialState = D3D12_RESOURCE_STATE_DEPTH_WRITE;
	}

	// buffer descriptor의 정보를 적용해준 버퍼를 새로 만들어준다.
	ComPtr<ID3D12Resource> buffer;
	{
		CD3DX12_HEAP_PROPERTIES heapProperty(D3D12_HEAP_TYPE_DEFAULT);
		ThrowIfFailed(device->CreateCommittedResource(
			&heapProperty,
			D3D12_HEAP_FLAG_NONE,
			&bufferDesc,
			initialState,
			nullptr,
			IID_PPV_ARGS(buffer.GetAddressOf())));
	}

	VEObject<Texture> newTexture = new Texture(buffer.Get(), initialState);

	// Render Target View.
	if (desc.usage & Texture::UsageRenderTarget)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heapDesc.NumDescriptors = 1;

		ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		rtvDesc.Format = bufferDesc.Format;
		switch (bufferDesc.Dimension)
		{
		case D3D12_RESOURCE_DIMENSION_TEXTURE1D:
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE1D;
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE2D:
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			break;
		case D3D12_RESOURCE_DIMENSION_TEXTURE3D:
			rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE3D;
			break;
		}

		device->CreateRenderTargetView(buffer.Get(), &rtvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
		newTexture->SetRenderTargetViewHeap(descriptorHeap.Get());
	}

	// Depth Stencil View.
	if (desc.usage & Texture::UsageDepthStencil)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
		heapDesc.NumDescriptors = 1;

		ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

		D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
		dsvDesc.Format = bufferDesc.Format;
		switch (desc.type)
		{
		case Texture::Type1D:
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE1D;
			break;
		case Texture::Type2D:
			dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
			break;
		case Texture::Type3D:
			break;
		}

		device->CreateDepthStencilView(buffer.Get(), &dsvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
		newTexture->SetDepthStencilViewHeap(descriptorHeap.Get());
	}

	// Shader Resource View
	if (desc.usage & Texture::UsageShaderRead)
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		heapDesc.NumDescriptors = 1;

		ComPtr<ID3D12DescriptorHeap> descriptorHeap;
		ThrowIfFailed(device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(descriptorHeap.GetAddressOf())));

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = bufferDesc.Format;
		switch (desc.type)
		{
		case Texture::Type1D:
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE1D;
			srvDesc.Texture1D.MipLevels = bufferDesc.MipLevels;
			break;
		case Texture::Type2D:
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = bufferDesc.MipLevels;
			break;
		case Texture::Type3D:
			srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE3D;
			srvDesc.Texture3D.MipLevels = bufferDesc.MipLevels;
			break;
		}
		device->CreateShaderResourceView(buffer.Get(), &srvDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());
		newTexture->SetShaderResourceViewHeap(descriptorHeap.Get());
	}

	return newTexture.Ptr();
}

VEObject<VERenderPipeline> GraphicsDevice::CreateRenderPipeline(const VERenderPipelineDescriptor& descriptor)
{
	ComPtr<ID3D12RootSignature> rootSignature;
	{
		CD3DX12_ROOT_PARAMETER slotRootParameters[3] = {};
		slotRootParameters[0].InitAsConstantBufferView(0);
		slotRootParameters[1].InitAsConstantBufferView(1);
		slotRootParameters[2].InitAsConstantBufferView(2);

		auto staticSamplers = ::Private::GetStaticSamplers();

		// Ref: ShapeApp.cpp
		 // A root signature is an array of root parameters.
		CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(3, slotRootParameters,
			static_cast<UINT>(staticSamplers.size()), staticSamplers.data(),
			D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

		// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
		ComPtr<ID3DBlob> serializedRootSig = nullptr;
		ComPtr<ID3DBlob> errorBlob = nullptr;
		HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
			serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

		if (errorBlob != nullptr)
		{
			::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		ThrowIfFailed(hr);

		ThrowIfFailed(device->CreateRootSignature(
			0,
			serializedRootSig->GetBufferPointer(),
			serializedRootSig->GetBufferSize(),
			IID_PPV_ARGS(rootSignature.GetAddressOf())));
	}

	ComPtr<ID3D12PipelineState> pipelineState;
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

		psoDesc.pRootSignature = rootSignature.Get();

		std::vector<D3D12_INPUT_ELEMENT_DESC> inputLayout;
		{
			UINT index = 0;
			inputLayout.reserve(descriptor.vertexDescriptor.attributes.size());
			for (const auto& attribute : descriptor.vertexDescriptor.attributes)
			{
				D3D12_INPUT_ELEMENT_DESC desc = {};
				desc.SemanticName = attribute.semanticName;
				desc.SemanticIndex = attribute.semanticIndex;
				desc.Format = VertexFormat(attribute.format);
				desc.AlignedByteOffset = attribute.offset;
				inputLayout.push_back(desc);
			}
		}
		psoDesc.InputLayout = { inputLayout.data(), (UINT)inputLayout.size() };
		psoDesc.VS = const_cast<VEObject<VEShader>&>(descriptor.vertexShader).DynamicCast<Shader>()->ByteCode();
		psoDesc.PS = const_cast<VEObject<VEShader>&>(descriptor.fragmentShader).DynamicCast<Shader>()->ByteCode();

		psoDesc.PrimitiveTopologyType = PrimitiveType(descriptor.inputPrimitiveTopology);

		psoDesc.NumRenderTargets = static_cast<ULONG>(descriptor.colorAttachments.size());
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		for (int i = 0; i < descriptor.colorAttachments.size(); ++i)
		{
			const auto& attachment = descriptor.colorAttachments[i];
			psoDesc.RTVFormats[i] = PixelFormat(attachment.pixelFormat);

			psoDesc.BlendState.RenderTarget[i].BlendEnable = attachment.blendingEnabled;
			psoDesc.BlendState.RenderTarget[i].BlendOp = BlendOperation(attachment.rgbBlendOperation);
			psoDesc.BlendState.RenderTarget[i].SrcBlend = BlendFactor(attachment.sourceRGBBlendFactor);
			psoDesc.BlendState.RenderTarget[i].DestBlend = BlendFactor(attachment.destinationRGBBlendFactor);
			psoDesc.BlendState.RenderTarget[i].BlendOpAlpha = BlendOperation(attachment.alphaBlendOperation);
			psoDesc.BlendState.RenderTarget[i].SrcBlendAlpha = BlendFactor(attachment.sourceAlphaBlendFactor);
			psoDesc.BlendState.RenderTarget[i].DestBlendAlpha = BlendFactor(attachment.destinationAlphaBlendFactor);
			psoDesc.BlendState.RenderTarget[i].RenderTargetWriteMask = attachment.writeMask;
		}

		psoDesc.SampleDesc.Count = descriptor.sampleCount;
		psoDesc.DSVFormat = PixelFormat(descriptor.depthStencilAttachmentPixelFormat);

		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

		// reversed-z를 사용하므로 depthfunction도 변경.
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_GREATER;
		psoDesc.SampleMask = UINT_MAX;
		ThrowIfFailed(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)));
	}

	return new RenderPipeline(pipelineState.Get(), rootSignature.Get());
}

VEObject<VEShader> GraphicsDevice::CreateShader(const std::vector<uint8_t>& code, const std::string& entry, VEShader::StageType stage)
{
	std::string shaderVersionName;
	switch (stage)
	{
	case VEShader::StageType::Vertex:
		shaderVersionName = "vs_5_0";
		break;
	case VEShader::StageType::Fragment:
		shaderVersionName = "ps_5_0";
		break;
		// default:
		// "Unsupported shader stage.;
	}

	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> byteCode;
	ComPtr<ID3DBlob> errors;
	HRESULT hr = D3DCompile2(code.data(), code.size(),
		nullptr, nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entry.c_str(),
		shaderVersionName.c_str(),
		compileFlags,
		0, 0, 0, 0, &byteCode, &errors);

	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());
	ThrowIfFailed(hr);

	return new Shader(byteCode.Get(), stage, entry);
}
