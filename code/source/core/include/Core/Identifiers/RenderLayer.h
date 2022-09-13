#pragma once
#include <cstdint>

namespace ids
{

enum class RenderLayer : uint64_t
{
	Default,
	Pause,
	COUNT // Special enum
};

} // namespace ids