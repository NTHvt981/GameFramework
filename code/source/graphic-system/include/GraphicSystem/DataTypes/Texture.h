#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/String.h"

namespace graphics
{

struct Texture
{
	ids::TextureId id;
	core::SizeI64 size;
	core::String filePath;
};

} // namespace graphics
