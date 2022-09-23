#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

struct File
{
	core::String name;
	core::String extension;
	core::String ToString() const
	{
		return name + "." + extension;
	}
};

const core::String extPng = "png";
const core::String extXml = "xml";

} // namespace file