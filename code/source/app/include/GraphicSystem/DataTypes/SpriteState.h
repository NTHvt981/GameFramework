#pragma once
#include <memory>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/DataTypes/Vector2.h"

namespace graphics
{

struct SpriteState
{
	std::weak_ptr<const SpriteDef> spriteDef;
	data_types::Vector2F position;
	float alpha;
};

} // namespace graphics