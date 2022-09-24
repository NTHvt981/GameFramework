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
	core::BoxI64 boundary;
	core::Vector2F origin;
	ids::TextureId textureId;
	std::weak_ptr<const Texture> textureRef;
};

} // namespace graphics
