#pragma once
#include "Core/DataTypes/String.h"
#include <vector>

namespace core
{

std::vector<String> Split(const String i_totalStr, const String i_delimiter);

} // namespace core