#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"
#include "VEPixelFormat.h"

namespace Venus
{
	class VE_API VETexture : public VERefCounter
	{
	public:
		enum Type
		{
			Type1D,
			Type2D,
			Type3D,
		};
		enum Usage : uint32_t
		{
			UsageNone = 0U,
			UsageShaderRead = 1U,
			UsageRenderTarget = 1U << 1,
			UsageDepthStencil = 1U << 2,
		};

		VETexture() = default;
		virtual ~VETexture() noexcept = default;

		virtual size_t Size() const = 0;
		virtual uint32_t Width() const = 0;
		virtual uint32_t Height() const = 0;
		virtual VEPixelFormat Format() const = 0;
	};

}