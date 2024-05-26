#pragma once
#include <vector>

namespace core
{
struct Texture;
} // namespace core

namespace xml
{

std::vector<core::Texture> LoadTexturesFile(const char* i_filePath);

} // namespace xml