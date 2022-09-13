#pragma once
#include "Core/DataTypes/String.h"
#include <optional>
#include <unordered_map>

namespace xml
{

// other classes use xml should define struct inherit this
struct XmlData
{
	virtual data_types::String GetKey() = 0;
};

} // namespace xml
