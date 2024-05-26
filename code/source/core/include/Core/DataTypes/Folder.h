#pragma once
#include "Core/DataTypes/String.h"

namespace core
{

struct Folder
{
	core::String name;
};
static const Folder BackwardFolder{ core::String("..") };

} // namespace core