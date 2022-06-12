#pragma once
#include "../../VEPixelFormat.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
    inline DXGI_FORMAT PixelFormat(VEPixelFormat format)
    {
        switch (format)
        {
        case VEPixelFormat::RGBA8Unorm:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case VEPixelFormat::RGBA8Snorm:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case VEPixelFormat::RGBA8Uint:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case VEPixelFormat::RGBA8Sint:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case VEPixelFormat::Depth24UnormStencil8:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    inline VEPixelFormat PixelFormat(DXGI_FORMAT format)
    {
        switch (format)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return VEPixelFormat::RGBA8Unorm;
        case DXGI_FORMAT_R8G8B8A8_SNORM:
            return VEPixelFormat::RGBA8Snorm;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return VEPixelFormat::RGBA8Uint;
        case DXGI_FORMAT_R8G8B8A8_SINT:
            return VEPixelFormat::RGBA8Sint;
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
            return VEPixelFormat::Depth24UnormStencil8;
        }
        return VEPixelFormat::None;
    }
}