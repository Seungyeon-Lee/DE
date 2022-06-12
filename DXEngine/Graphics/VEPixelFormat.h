#pragma once
#include "../VEInclude.h"

namespace Venus
{
	enum class VEPixelFormat
	{
        None,
        RGBA8Unorm,
        RGBA8Snorm,
        RGBA8Uint,
        RGBA8Sint,
        Depth24UnormStencil8,
	};

    inline uint32_t PixelFormatSize(VEPixelFormat format)
    {
        switch (format)
        {
        case VEPixelFormat::RGBA8Unorm:
        case VEPixelFormat::RGBA8Snorm:
        case VEPixelFormat::RGBA8Uint:
        case VEPixelFormat::RGBA8Sint:
        case VEPixelFormat::Depth24UnormStencil8:
            return 4;
        }
        return 0;
    }
}