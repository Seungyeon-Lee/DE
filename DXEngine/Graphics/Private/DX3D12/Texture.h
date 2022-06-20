#pragma once
#include "../../VETexture.h"
#include "DXInclude.h"
#include "../../VEPixelFormat.h"

namespace Venus::Private::Direct3D12
{
	class Texture final : public VETexture
	{
	public:
		Texture(ID3D12Resource*, D3D12_RESOURCE_STATES);
		~Texture() noexcept = default;

		size_t Size() const override;
		uint32_t Width() const { return width; }
		uint32_t Height() const { return height; }
		VEPixelFormat Format() const { return format; }

		ID3D12Resource* Resource() const { return buffer.Get(); }
		D3D12_RESOURCE_STATES InitialState() const { return initialState; }

		void SetRenderTargetViewHeap(ID3D12DescriptorHeap* heap);
		void SetDepthStencilViewHeap(ID3D12DescriptorHeap* heap);
		void SetShaderResourceViewHeap(ID3D12DescriptorHeap* heap);

		D3D12_CPU_DESCRIPTOR_HANDLE ShaderResourceView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE RenderTargetView() const;
		D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;

	private:
		uint32_t width;
		uint32_t height;
		VEPixelFormat format;

		ComPtr<ID3D12Resource> buffer;
		D3D12_RESOURCE_STATES initialState;
		ComPtr<ID3D12DescriptorHeap> renderTargetViewHeap;
		ComPtr<ID3D12DescriptorHeap> depthStencilViewHeap;
		ComPtr<ID3D12DescriptorHeap> shaderResourceViewHeap;
	};
}

