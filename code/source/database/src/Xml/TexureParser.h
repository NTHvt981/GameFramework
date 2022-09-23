#pragma once
#include "GraphicSystem/DataTypes/Texture.h"
#include <vector>

namespace xml
{

std::vector<graphics::Texture> LoadFile(const char* i_filePath);

} // namespace xml