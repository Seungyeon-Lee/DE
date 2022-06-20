#pragma once
#include "../../VESwapChain.h"
#include "DXInclude.h"
#include "../../../Common/VEObject.h"
#include "GraphicsDevice.h"
#include "Texture.h"

namespace Venus
{
	class VEWindow;

	namespace Private::Direct3D12
	{
		class CommandQueue;

		class SwapChain final : public VESwapChain
		{
		public:
			SwapChain(GraphicsDevice*, CommandQueue*, const VEWindow*);
			~SwapChain() noexcept = default;

			uint32_t Width() override { return width; }
			uint32_t Height() override { return height; }

			const VETexture* CurrentColorTexture() const override;
			const VETexture* DepthStencilTexture() const override;

			void Resize(uint32_t width, uint32_t height) override;
			void Present() override;

		private:
			void SetupChainTexture();
			void SetupDepthStencil();

			uint32_t width;
			uint32_t height;

			UINT currentTextureIndex;
			mutable VEObject<Texture> chainTexture[SwapChainBufferCount];
			mutable VEObject<Texture> depthStencilTexture;

			ComPtr<IDXGISwapChain3> swapChain;
			VEObject<GraphicsDevice> device;
		};
	}
}
