#pragma once
#include <memory>
#include "Core/Identifiers/SpriteId.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Texture.h"
#include "Core/DataTypes/Vector2.h"

namespace graphics
{

struct SpriteDef
{
	core::SpriteId id;
	core::BoxI64 textureBoundary;
	core::Vector2F origin;
	core::TextureId textureId;
	std::weak_ptr<const Texture> textureRef;
};

} // namespace graphics
