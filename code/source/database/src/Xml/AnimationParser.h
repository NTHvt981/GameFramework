#pragma once
#include <vector>

namespace graphics
{
struct AnimationDef;
} // namespace graphics

namespace xml
{

std::vector<graphics::AnimationDef> LoadAnimationsFile(const char* i_filePath);

} // namespace xml