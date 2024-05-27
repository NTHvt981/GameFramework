#pragma once
#include <vector>

namespace core
{
struct Sound;
} // namespace core

namespace xml
{

std::vector<core::Sound> LoadSoundsFile(const char* i_filePath);

} // namespace xml