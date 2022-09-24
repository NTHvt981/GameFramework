#pragma once
#include <vector>
#include <memory>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/Identifiers/AnimationId.h"

namespace graphics
{

struct AnimationFrameDef
{
	ids::SpriteId spriteId;
	std::weak_ptr<const SpriteDef> spriteRef;
	uint64_t timeSpan;
};

struct AnimationDef
{
	ids::AnimationId id;
	std::vector<AnimationFrameDef> frames;
};

} // namespace graphics