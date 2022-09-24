#pragma once
#include <cstdint>

namespace ids
{

enum class DrawMode : uint64_t
{
	Absolute,	// Use for GUI, UI elements like health bar, button, ...
	Relative	// Use for game entites like player, enemies, ... .Recalculate draw position base on camera
};

} // namespace ids