#pragma once
#include <vector>

namespace Venus
{
    enum class VEVertexFormat
    {
        Invalid = 0,

        Float,
        Float2,
        Float3,
        Float4,
    };

    struct VEVertexAttributeDescriptor
    {
        VEVertexFormat format;
        const char* semanticName;
        uint32_t semanticIndex;
        uint32_t offset;
    };

    struct VEVertexDescriptor
    {
        std::vector<VEVertexAttributeDescriptor> attributes;
    };
}
