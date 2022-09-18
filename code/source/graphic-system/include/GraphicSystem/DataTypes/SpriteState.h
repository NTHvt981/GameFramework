#pragma once
#include <memory>
#include <stdint.h>
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Identifiers/RenderLayer.h"

namespace graphics
{

struct SpriteState
{
	using Id = uint64_t;
	const Id id;
	SpriteState(Id i_id) : id(i_id) {};
	std::weak_ptr<const SpriteDef> spriteDef;
	core::Vector2F position = core::Vector2F();
	float alpha = 1;
	ids::RenderLayer renderLayer = ids::RenderLayer::Default;
};

} // namespace graphics