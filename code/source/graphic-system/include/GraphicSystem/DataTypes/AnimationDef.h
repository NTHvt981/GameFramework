#pragma once
#include <vector>
#include <memory>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/Identifiers/AnimationId.h"

namespace graphics
{

struct AnimationFrameDef
{
	std::weak_ptr<const SpriteDef> sprite;
	uint64_t time;
};

struct AnimationDef
{
	ids::AnimationId id;
	std::vector<AnimationFrameDef> frames;
	float alpha;
};

} // namespace graphics