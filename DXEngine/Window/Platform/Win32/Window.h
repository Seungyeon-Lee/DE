#pragma once
#include "../../VEWindow.h"
#include <windows.h>

namespace Venus
{
	class Window : public VEWindow
	{
	public:
		Window();
		~Window();

		void Create() override;
		void Destroy() override;

		void Show() override;
		void Hide() override;

		void* Handle() const override { return handle; }

		uint32_t Width() const override { return width; }
		uint32_t Height() const override { return height; }
		float AspectRatio() const override;

	protected:
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HWND handle;

		uint32_t width;
		uint32_t height;
	};
}