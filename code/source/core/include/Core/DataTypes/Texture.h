#pragma once
#include "Core/Identifiers/TextureId.h"
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/String.h"

namespace core
{

struct Texture
{
	TextureId id;
	SizeI64 size;
	String filePath;
};

} // namespace core
