#pragma once
#include <cstdint>

#ifdef DX_DYNAMIC
#    ifndef DX_API
#       ifdef DLL_EXPORTS
#           pragma message("Build for DLL.")
#           define DX_API __declspec(dllexport)
#       else
#           define DX_API __declspec(dllimport)
#       endif
#    endif
#else
#    define DX_API
#	 define EPSILON 1.0e-6
#	 define PI		3.1415926535898f
#endif

#	 define WINDOW_CLASS_NAME L"VEWindowClass"

template<class T>
decltype(auto) Clamp(const T& value, const T& min, const T& max)
{
	return value < min ? min : value > max ? max : value;
}
