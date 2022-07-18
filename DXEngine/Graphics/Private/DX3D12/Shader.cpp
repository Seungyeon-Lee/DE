#include "Shader.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

Shader::Shader(ID3DBlob* byteCode, VEShader::StageType stage, const std::string& entry)
	: stage(stage)
	, entry(entry)
	, byteCode(byteCode)
{

}

D3D12_SHADER_BYTECODE Shader::ByteCode() const
{
	return { reinterpret_cast<BYTE*>(byteCode->GetBufferPointer()), byteCode->GetBufferSize() };
}
