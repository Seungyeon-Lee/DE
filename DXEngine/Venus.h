#pragma once
#include <cstdint>
#include <cassert>
#include <cmath>
#include <memory>

#ifdef VE_DYNAMIC
#    ifndef VE_API
#       ifdef DLL_EXPORTS
#           pragma message("Build for DLL.")
#           define VE_API __declspec(dllexport)
#       else
#           define VE_API __declspec(dllimport)
#       endif
#    endif
#else
#    define VE_API
#	 define EPSILON 1.0e-6
#	 define PI		3.1415926535898f
#endif

#	 define WINDOW_CLASS_NAME L"VEWindowClass"

namespace Venus
{
	template<class T>
	decltype(auto) Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : value > max ? max : value;
	}
}