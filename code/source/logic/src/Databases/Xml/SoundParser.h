#pragma once
#include <vector>

namespace audios
{
struct Sound;
} // namespace graphics

namespace xml
{

std::vector<audios::Sound> LoadSoundsFile(const char* i_filePath);

} // namespace xml