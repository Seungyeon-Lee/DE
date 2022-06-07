#include "VEGraphicsDevice.h"
#include "Private/GraphicsAPI.h"
#include "Private/DX3D12/GraphicsDevice.h"

using namespace Venus;
VEGraphicsDevice* VEGraphicsDevice::CreateGraphicsDevice() {
	return Venus::Private::CreateGraphicsDevice();
}
