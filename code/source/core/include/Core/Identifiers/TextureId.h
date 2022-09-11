#pragma once
#include <cstdint>

namespace ids
{

enum class TextureId : uint64_t
{
	Enemies,
	Player,
	PlayerHealth,
	OtherObjects,
	BlackScreen,
	Boss,
	Opening,
	Rollout,
	Item,
	CollisionDebug,
	COUNT // Special enum
};

} // namespace ids