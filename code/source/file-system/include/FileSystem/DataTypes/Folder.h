#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

struct Folder
{
	data_types::String name;
};
static const Folder BackwardFolder{ data_types::String("..") };

} // namespace file