#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/DataTypes/Box.h"

namespace graphics
{

struct Texture
{
	ids::TextureId id;
	core::BoxI64 bound;
};

} // namespace graphics