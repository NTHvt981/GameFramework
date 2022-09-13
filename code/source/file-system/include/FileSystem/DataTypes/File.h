#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

struct File
{
	data_types::String name;
	data_types::String extension;
};

const data_types::String extPng = "png";

} // namespace file