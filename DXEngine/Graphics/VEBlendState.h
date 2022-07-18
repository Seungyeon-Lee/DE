#pragma once

namespace Venus
{
    enum VEColorWriteMask
    {
        ColorWriteMaskNone = 0x0,
        ColorWriteMaskRed = 0x1,
        ColorWriteMaskGreen = 0x2,
        ColorWriteMaskBlue = 0x4,
        ColorWriteMaskAlpha = 0x8,
        ColorWriteMaskAll = 0xf,
    };

    enum class VEBlendOperation
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max
    };

    enum class VEBlendFactor
    {
        Zero,
        One,
        SourceColor,
        OneMinusSourceColor,
        SourceAlpha,
        OneMinusSourceAlpha,
        DestinationColor,
        OneMinusDestinationColor,
        DestinationAlpha,
        OneMinusDestinationAlpha,
        SourceAlphaSaturated,
        BlendFactor,
        OneMinusBlendFactor,
    };
}