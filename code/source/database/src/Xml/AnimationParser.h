#pragma once
#include "GraphicSystem/DataTypes/AnimationDef.h"
#include <vector>

namespace xml
{

std::vector<graphics::AnimationDef> LoadAnimationsFile(const char* i_filePath);

} // namespace xml