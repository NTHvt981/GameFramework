#pragma once
#include <memory>
#include <stdint.h>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/DataTypes/Vector2.h"

namespace graphics
{

struct SpriteState
{
	using Id = uint64_t;
	Id id;
	std::weak_ptr<const SpriteDef> spriteDef;
	data_types::Vector2F position;
	float alpha;
};

} // namespace graphics