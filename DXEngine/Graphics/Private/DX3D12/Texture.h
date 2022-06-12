#pragma once
#include "../../VETexture.h"
#include "DXInclude.h"
#include "../../VEPixelFormat.h"

namespace Venus::Private::Direct3D12
{
	class Texture final : public VETexture
	{
		size_t Size() const override;
		uint32_t Width() const override;
		uint32_t Height() const override;
		VEPixelFormat Format() const override;
	};
}

