#include "VEGraphicsDevice.h"
#include "Private/GraphicsAPI.h"
#include "Private/DX3D12/GraphicsDevice.h"
#include <fstream>

using namespace Venus;

VEGraphicsDevice* VEGraphicsDevice::CreateGraphicsDevice() 
{
	return Venus::Private::CreateGraphicsDevice();
}

VEObject<VEShader> VEGraphicsDevice::CreateShader(const std::wstring& path, const std::string& entry, VEShader::StageType stage)
{
	std::ifstream file(path.data(), std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* code = new char[size];

		file.seekg(0, std::ios::beg);
		file.read(code, size);
		auto result = CreateShader(std::vector<uint8_t>(code, code + size), entry, stage);

		delete[] code;
		file.close();

		return result;
	}
	return nullptr;
}
