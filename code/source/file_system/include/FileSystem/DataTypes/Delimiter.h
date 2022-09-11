#pragma once
#include "Core/DataTypes/String.h"

namespace files
{

class Delimiter
{
public:
	data_types::String GetName() const
	{
		return "//";
	};
};

} // namespace files