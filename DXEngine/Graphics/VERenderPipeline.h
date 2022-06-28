#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VE_API VERenderPipeline : public VERefCounter
	{
	public:
		VERenderPipeline() = default;
		virtual ~VERenderPipeline() noexcept = default;
	};
}