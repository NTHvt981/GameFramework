#pragma once
#include "Core/DataTypes/Iterator.h"
#include <cstdint>

namespace core
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
	CollisionDebug
};

typedef Iterator<TextureId, TextureId::Enemies, TextureId::CollisionDebug> TextureIdIterators;

} // namespace core