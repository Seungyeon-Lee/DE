#include "VEWindow.h"
#include <exception>

VEWindow::VEWindow()
    : hWnd(nullptr)
    , width(0)
    , height(0)
{
}

VEWindow::~VEWindow()
{
}

void VEWindow::Create() {
    if (hWnd)
        return ;

    // Register the window class.
    WNDCLASSEXW windowClass = { 0 };
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = ::GetModuleHandleW(NULL);
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = WINDOW_CLASS_NAME;

    ::RegisterClassExW(&windowClass);

    // Create the window.
    hWnd = CreateWindowExW(
        0,                              // Optional window styles.
        WINDOW_CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        ::GetModuleHandleW(NULL),  // Instance handle
        NULL        // Additional application data
    );

    if (!hWnd)
        throw std::exception("Failed Create Window");

    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw
    ::SetLastError(0);
    if (!::SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)this))
    {
        if (::GetLastError())
            throw std::exception("Failed SetWindowLongPtrW");
    }

    ::ShowWindow(hWnd, 1);
}

void VEWindow::Destroy()
{
    if (hWnd)
    {
        ::PostMessageW(hWnd, WM_CLOSE, 0, 0);
        hWnd = NULL;
    }
}

float VEWindow::AspectRatio() const
{
    return static_cast<float>(width) / static_cast<float>(height);
}

void VEWindow::AddResizeEventListener(EventListener listener, ResizeEventCallback callback)
{
    listeners.emplace(listener, callback);
}

void VEWindow::RemoveResizeEventListener(EventListener listener)
{
    listeners.erase(listener);
}


LRESULT VEWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    VEWindow* window = (VEWindow*)::GetWindowLongPtrW(hWnd, GWLP_USERDATA);
    if (window)
    {
        switch (message)
        {
        case WM_SIZE:
        {
            size_t width = LOWORD(lParam);
            size_t height = HIWORD(lParam);
            if (window->width != width || window->height != height)
            {
                window->width = width;
                window->height = height;

                // broadcast.
                for (const auto& [key, value] : window->listeners)
                {
                    value(window->width, window->height);
                }
            }
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    // Handle any messages the switch statement didn't.
    return ::DefWindowProcW(hWnd, message, wParam, lParam);
}