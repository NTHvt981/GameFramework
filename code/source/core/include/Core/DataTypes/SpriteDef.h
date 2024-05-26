#pragma once
#include <memory>
#include "Core/Identifiers/SpriteId.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Texture.h"
#include "Core/DataTypes/Vector2.h"

namespace core
{

struct SpriteDef
{
	SpriteId id;
	BoxI64 textureBoundary;
	Vector2F origin;
	TextureId textureId;
	std::weak_ptr<const Texture> textureRef;
};

} // namespace core
