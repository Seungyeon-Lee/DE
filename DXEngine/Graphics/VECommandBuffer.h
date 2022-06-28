#pragma once
#include "../VEInclude.h"
#include "VERenderCommandEncoder.h"
#include "VECopyCommandEncoder.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VE_API VECommandBuffer : public VERefCounter
	{
	public:
		VECommandBuffer() = default;
		virtual ~VECommandBuffer() noexcept = default;

		virtual VEObject<VERenderCommandEncoder> CreateRenderCommandEncoder() = 0;
		virtual VEObject<VECopyCommandEncoder> CreateCopyCommandEncoder() = 0;

		virtual void Commit() = 0;
	};
}
