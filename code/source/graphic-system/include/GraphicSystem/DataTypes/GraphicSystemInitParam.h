#pragma once
#include <optional>
#include <Windows.h>
#include "Core/Identifiers/APIMode.h"

namespace graphics
{

struct GraphicSystemInitParam
{
	ids::APIMode apiMode;
	std::optional<HWND> optHwnd;
};

} // namespace graphics