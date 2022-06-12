#include "GPUBuffer.h"

using namespace Venus;
using namespace Venus::Private::Direct3D12;

// Ref. DX12 : UploadBuffer.h
GPUBuffer::GPUBuffer(ID3D12Resource* buffer, CPUCacheMode mode, D3D12_RESOURCE_STATES initialState)
	: writable(mode == CPUCacheMode::UPLOAD)
	, readable(mode == CPUCacheMode::READBACK)
	, buffer(buffer)
	, initialState(initialState)
{
	size = buffer->GetDesc().Width;
}

bool GPUBuffer::WriteData(const void* data, size_t size)
{
	BYTE* mappedGPUData = nullptr;
	D3D12_RANGE readRange{ 0, 0 }; // don't read.
	if (SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGPUData))))
	{
		memcpy(mappedGPUData, data, size);

		D3D12_RANGE writeRange(0, size); // write size for optimize hint.
		buffer->Unmap(0, &writeRange);
		return true;
	}
	return false;
}

bool GPUBuffer::WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize)
{
	BYTE* mappedGpuData = nullptr;
	D3D12_RANGE readRange{ 0, 0 }; // �� ��. 0 ~ 0 ������ �����͸� �д´�.

	// reinterpret_cast : ������ ������ Ÿ�Գ��� ��ȯ�� ����Ѵ�.
	// void** Ÿ������ BYTE*�� ��ȯ�ϴ� ���� ����Ѵ�.
	if (SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGpuData))))
	{
		size_t rowPitch = width * formatSize;
		size_t alignedRowPitch = AlignTextureRowPitch(rowPitch);

		// �����͸� �о�´�.
		// DX������ Buffer�� Resource�̴�. Align���� ������ ������ �߻��ϱ� ������ rowPitch�� ����Ѵ�.
		// Constant buffer elements need to be multiples of 256 bytes.
		// This is because the hardware can only view constant data 
		// at m*256 byte offsets and of n*256 byte lengths. 
		const BYTE* cpuData = reinterpret_cast<const BYTE*>(const_cast<void*>(data));
		for (size_t i = 0; i < height; ++i)
		{
			memcpy(mappedGpuData + alignedRowPitch * i,
				reinterpret_cast<const void*>(cpuData + rowPitch * i),
				rowPitch);
		}

		D3D12_RANGE writeRange(0, rowPitch * height); // write size for optimize hint.
		buffer->Unmap(0, &writeRange);
		return true;
	}
	return false;
}

bool GPUBuffer::ReadData(void* data, size_t size)
{
	BYTE* mappedGpuData = nullptr;
	D3D12_RANGE readRange{ 0, size }; // 0 ~ size������ �����͸� �д´�.

	if (SUCCEEDED(buffer->Map(0, &readRange, reinterpret_cast<void**>(&mappedGpuData))))
	{
		memcpy(data, mappedGpuData, size);

		D3D12_RANGE writeRange(0, 0);
		buffer->Unmap(0, &writeRange);
		return true;
	}
	return false;
}