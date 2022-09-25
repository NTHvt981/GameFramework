#pragma once
#include <cstdint>

namespace core
{

enum class AnimationId : uint64_t
{
	WormMoveLeft,
	WormMoveRight,
	COUNT // Special enum
};

} // namespace core