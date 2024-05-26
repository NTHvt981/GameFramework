#pragma once
#include <vector>

namespace core
{
struct SpriteDef;
} // namespace core

namespace xml
{

std::vector<core::SpriteDef> LoadSpritesFile(const char* i_filePath);

} // namespace xml