#include "VEGraphicsDevice.h"
#include "Private/GraphicsAPI.h"

using namespace Venus;
VEGraphicsDevice* VEGraphicsDevice::CreateGraphicsDevice() {
	return GraphicsAPI::CreateGraphicsDevice();
}
