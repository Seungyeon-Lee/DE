#pragma once
#include "Venus.h"
#include "VEInclude.h"

using namespace Venus;

namespace VenusApp
{
    struct VELight
    {
        VEVector3 strength = { 0.5f, 0.5f, 0.5f };
        float falloffStart = 1.0f;                          // point/spot light only
        VEVector3 direction = { 0.0f, -1.0f, 0.0f };        // directional/spot light only
        float falloffEnd = 10.0f;                           // point/spot light only
        VEVector3 position = { 0.0f, 0.0f, 0.0f };          // point/spot light only
        float spotPower = 64.0f;                            // spot light only
    };
}
