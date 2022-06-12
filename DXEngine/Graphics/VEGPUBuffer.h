#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VE_API VEGPUBuffer : public VERefCounter
	{
	public:
		enum class CPUCacheMode
		{
			DEFAULT = 0,
			UPLOAD,
			READBACK
		};

		VEGPUBuffer() = default;
		virtual ~VEGPUBuffer() noexcept = default;

		virtual size_t Size() const = 0;
		virtual bool IsWritable() const = 0;
		virtual bool IsReadable() const = 0;

		virtual bool WriteData(const void* data, size_t size) = 0;
		virtual bool WriteDataForTexture(const void* data, uint32_t width, uint32_t height, uint32_t formatSize) = 0;
		virtual bool ReadData(void* data, size_t size) = 0;
	};

}