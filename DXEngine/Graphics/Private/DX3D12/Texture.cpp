#include "Texture.h"
#include "PixelFormat.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

Texture::Texture(ID3D12Resource* buffer, D3D12_RESOURCE_STATES initialState)
	: buffer(buffer)
	, initialState(initialState)
{
	D3D12_RESOURCE_DESC desc = buffer->GetDesc();
	width = static_cast<uint32_t>(desc.Width);
	height = static_cast<uint32_t>(desc.Height);
	format = PixelFormat(desc.Format);
}

size_t Texture::Size() const
{
	return AlignTextureRowPitch(width * PixelFormatSize(format)) * height;
}
