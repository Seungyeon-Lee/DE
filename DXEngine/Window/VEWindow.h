#pragma once
#include "../VEInclude.h"
#include "../Common/VEObject.h"

namespace Venus
{
	class VE_API VEWindow : public VERefCounter
	{
	public:
		virtual ~VEWindow() noexcept = default;

		static VEWindow* CreatePlatformWindow();

		virtual void Create() = 0;
		virtual void Destroy() = 0;

		virtual void Show() = 0;
		virtual void Hide() = 0;

		virtual void* Handle() const = 0;

		virtual uint32_t Width() const = 0;
		virtual uint32_t Height() const = 0;
		virtual float AspectRatio() const = 0;

	protected:
		VEWindow() = default;
	};
}