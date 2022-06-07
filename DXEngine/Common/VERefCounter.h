#pragma once
#include "../VEInclude.h"

namespace Venus
{
	class VE_API VERefCounter
	{
	public:
		VERefCounter();
		virtual ~VERefCounter() noexcept;

		uint32_t AddRef();
		uint32_t Release();
		uint32_t RefCount() const;

	private:
		struct VE_API std::atomic<unsigned int> refCount;
	};
}