#pragma once
#include <cstdint>

namespace core
{

enum class CollisionLayer : uint64_t
{
	Player,
	Enemy,
	Wall,
	Missile
};

} // namespace core