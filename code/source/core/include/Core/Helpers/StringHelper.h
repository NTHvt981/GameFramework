#pragma once
#include "Core/DataTypes/String.h"
#include <vector>

namespace data_types::string
{

std::vector<String> Split(const String i_totalStr, const String i_delimiter);

} // namespace data_types::string