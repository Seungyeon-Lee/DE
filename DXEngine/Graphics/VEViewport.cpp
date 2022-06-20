#include "VEViewport.h"

using namespace Venus;

VEViewport::VEViewport()
    : origin(), size(), nearDepth(0.f), farDepth(0.f)
{}

VEViewport::VEViewport(VEPoint origin, VESize size, float nearDepth, float farDepth)
    : origin(origin), size(size), nearDepth(nearDepth), farDepth(farDepth)
{}

VEViewport::VEViewport(float x, float y, float width, float height, float nearDepth, float farDepth)
    : origin(x, y), size(width, height), nearDepth(nearDepth), farDepth(farDepth)
{}