#pragma once
#include <vector>
#include "Databases/Xml/CommonParser.h"
#include "Core/Identifiers/TextureId.h"
#include "Core/DataTypes/AnimationDef.h"

namespace xml
{

std::vector<core::AnimationDef> LoadAnimationsFile(const char* i_filePath);

} // namespace xml