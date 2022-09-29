#pragma once
#include <vector>
#include <memory>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/Identifiers/AnimationId.h"

namespace graphics
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

} // namespace graphics