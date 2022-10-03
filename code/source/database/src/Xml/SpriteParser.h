#pragma once
#include <vector>

namespace graphics
{
struct SpriteDef;
} // namespace graphics

namespace xml
{

std::vector<graphics::SpriteDef> LoadSpritesFile(const char* i_filePath);

} // namespace xml