#pragma once
#include "Venus.h"
#include "VEInclude.h"
#include "VEMesh.h"
#include "VEMaterial.h"

using namespace Venus;

namespace VenusApp
{
    struct VEModel
    {
        VEMatrix4 world;
        VEMatrix4 texTransform;

        std::vector<VEMesh> meshes;
        VEMaterial material;
    };
}
