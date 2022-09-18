#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

struct Folder
{
	core::String name;
};
static const Folder BackwardFolder{ core::String("..") };

} // namespace file