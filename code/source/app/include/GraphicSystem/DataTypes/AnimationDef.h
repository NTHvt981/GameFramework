#pragma once
#include <array>
#include <valarray>
#include <memory>
#include "GraphicSystem/DataTypes/SpriteDef.h"

namespace graphics
{

struct AnimationFrameDef
{
	std::weak_ptr<const SpriteDef> sprite;
	uint64_t time;
};

struct AnimationDef
{
	std::valarray<AnimationFrameDef> frames;
	float alpha;
};

} // namespace graphics