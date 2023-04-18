#pragma once
#include "Venus.h"
#include "VEInclude.h"

using namespace Venus;

namespace VenusApp
{
    struct VEMaterial
    {
        VELinearColor diffuseAlbedo = { 1.0f, 1.0f, 1.0f, 1.0f };
        VEVector3 fresnelR0 = { 0.01f, 0.01f, 0.01f };
        float roughness = 0.25f;
        VEMatrix4 matTransform = {};
    };
}
