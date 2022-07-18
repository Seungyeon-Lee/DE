#pragma once
#include "../../VEShader.h"
#include "DXInclude.h"

namespace Venus::Private::Direct3D12
{
    class Shader final : public VEShader
    {
    public:
        Shader(ID3DBlob* byteCode, VEShader::StageType stage, const std::string& entry);
        ~Shader() noexcept = default;

        D3D12_SHADER_BYTECODE ByteCode() const;

    private:
        VEShader::StageType stage;
        std::string entry;
        ComPtr<ID3DBlob> byteCode;
    }; 
}
