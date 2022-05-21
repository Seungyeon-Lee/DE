#include "VEGraphicsDevice.h"
#include "GraphicsAPI.h"

using namespace Venus;
VEGraphicsDevice* VEGraphicsDevice::CreateGraphicsDevice() {
	return GraphicsAPI::CreateGraphicsDevice();
}
