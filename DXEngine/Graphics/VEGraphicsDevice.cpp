#include "VEGraphicsDevice.h"
#include "GraphicsAPI.h"

VEGraphicsDevice* VEGraphicsDevice::CreateGraphicsDevice() {
	return GraphicsAPI::CreateGraphicsDevice();
}
