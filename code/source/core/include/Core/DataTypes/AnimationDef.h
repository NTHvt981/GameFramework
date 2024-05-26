#pragma once
#include <vector>
#include <memory>
#include "Core/DataTypes/SpriteDef.h"
#include "Core/Identifiers/AnimationId.h"

namespace core
{

struct AnimationFrameDef
{
	core::SpriteId spriteId;
	std::weak_ptr<const SpriteDef> spriteDefRef;
	uint64_t duration;
};

struct AnimationDef
{
	core::AnimationId id;
	std::vector<AnimationFrameDef> frames;
};

} // namespace core