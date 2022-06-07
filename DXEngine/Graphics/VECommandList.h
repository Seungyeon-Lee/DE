#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VE_API VECommandList : public VERefCounter
	{
	public:
		VECommandList() = default;
		virtual ~VECommandList() noexcept = default;
	};
}