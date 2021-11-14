#pragma once
#include "DXEngine.h"
#include <Windows.h>
#include <functional>
#include <map>

class DX_API VEWindow
{
public:
	VEWindow();
	~VEWindow();

	void Create();
	void Destroy();

	void* Handle() const { return hWnd; }

	size_t Width() const { return width; }
	size_t Height() const { return height; }
	using EventListener = const void*;
	using ResizeEventCallback = std::function<void(size_t, size_t)>;
	float AspectRatio() const;

	void AddResizeEventListener(EventListener listener, ResizeEventCallback callback);
	void RemoveResizeEventListener(EventListener listener);

protected:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;

	size_t width;
	size_t height;

	std::map<EventListener, ResizeEventCallback> listeners;
};