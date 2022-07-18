#pragma once
#include "../../VEPixelFormat.h"
#include "../../VEVertexDescriptor.h"
#include "../../VERenderPipeline.h"
#include "../../VEBlendState.h"
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

    inline DXGI_FORMAT VertexFormat(VEVertexFormat format)
    {
        switch (format)
        {
        case VEVertexFormat::Float:
            return DXGI_FORMAT_D32_FLOAT;
        case VEVertexFormat::Float2:
            return DXGI_FORMAT_R32G32_FLOAT;
        case VEVertexFormat::Float3:
            return DXGI_FORMAT_R32G32B32_FLOAT;
        case VEVertexFormat::Float4:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
        return DXGI_FORMAT_UNKNOWN;
    }

    inline D3D12_PRIMITIVE_TOPOLOGY_TYPE PrimitiveType(VEPrimitiveTopologyType type)
    {
        switch (type)
        {
        case VEPrimitiveTopologyType::Point:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
        case VEPrimitiveTopologyType::Line:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
        case VEPrimitiveTopologyType::Triangle:
            return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        }
        return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
    }

    inline D3D12_BLEND_OP BlendOperation(VEBlendOperation type)
    {
        switch (type)
        {
        case VEBlendOperation::Add:
            return D3D12_BLEND_OP_ADD;
        case VEBlendOperation::Subtract:
            return D3D12_BLEND_OP_SUBTRACT;
        case VEBlendOperation::ReverseSubtract:
            return D3D12_BLEND_OP_REV_SUBTRACT;
        case VEBlendOperation::Min:
            return D3D12_BLEND_OP_MIN;
        case VEBlendOperation::Max:
            return D3D12_BLEND_OP_MAX;
        // default:
        // ASSERT
        }
        return D3D12_BLEND_OP_ADD;
    }

    inline D3D12_BLEND BlendFactor(VEBlendFactor type)
    {
        switch (type)
        {
        case VEBlendFactor::Zero:
            return D3D12_BLEND_ZERO;
        case VEBlendFactor::One:
            return D3D12_BLEND_ONE;
        case VEBlendFactor::SourceColor:
            return D3D12_BLEND_SRC_COLOR;
        case VEBlendFactor::OneMinusSourceColor:
            return D3D12_BLEND_INV_SRC_COLOR;
        case VEBlendFactor::SourceAlpha:
            return D3D12_BLEND_SRC_ALPHA;
        case VEBlendFactor::OneMinusSourceAlpha:
            return D3D12_BLEND_INV_SRC_ALPHA;
        case VEBlendFactor::DestinationColor:
            return D3D12_BLEND_DEST_COLOR;
        case VEBlendFactor::OneMinusDestinationColor:
            return D3D12_BLEND_INV_DEST_COLOR;
        case VEBlendFactor::DestinationAlpha:
            return D3D12_BLEND_DEST_ALPHA;
        case VEBlendFactor::OneMinusDestinationAlpha:
            return D3D12_BLEND_INV_DEST_ALPHA;
        case VEBlendFactor::SourceAlphaSaturated:
            return D3D12_BLEND_SRC_ALPHA_SAT;
        case VEBlendFactor::BlendFactor:
            return D3D12_BLEND_BLEND_FACTOR;
        case VEBlendFactor::OneMinusBlendFactor:
            return D3D12_BLEND_INV_BLEND_FACTOR;
        // default:
        // ASSERT
        }
        return D3D12_BLEND_ONE;
    }
}
