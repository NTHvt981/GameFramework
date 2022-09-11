#pragma once
#include <memory>
#include "Core/Identifiers/SpriteId.h"
#include "Core/DataTypes/Box.h"
#include "GraphicSystem/DataTypes/Texture.h"
#include "Core/DataTypes/Vector2.h"

namespace graphics
{

struct SpriteDef
{
	ids::SpriteId id;
	data_types::BoxI64 bound;
	data_types::Vector2F origin;
	std::weak_ptr<const Texture> texture;
};

} // namespace graphics