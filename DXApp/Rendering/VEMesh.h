#pragma once
#include "Venus.h"
#include "VEInclude.h"

using namespace Venus;

namespace VenusApp
{
    struct VEVertex
    {
        VEVector3 pos;
        VEVector3 normal;
        VELinearColor color;
        VEVector2 texcoord;
    };

    struct VEMesh
    {
        std::vector<VEVertex> vertices;
        VEObject<VEGPUBuffer> vertexBuffer;
    };
}