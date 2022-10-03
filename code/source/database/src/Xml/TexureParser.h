#pragma once
#include <vector>

namespace graphics
{
struct Texture;
} // namespace graphics

namespace xml
{

std::vector<graphics::Texture> LoadTexturesFile(const char* i_filePath);

} // namespace xml