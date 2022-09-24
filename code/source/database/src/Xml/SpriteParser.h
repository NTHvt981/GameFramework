#pragma once
#include "GraphicSystem/DataTypes/SpriteDef.h"
#include <vector>

namespace xml
{

std::vector<graphics::SpriteDef> LoadSpritesFile(const char* i_filePath);

} // namespace xml