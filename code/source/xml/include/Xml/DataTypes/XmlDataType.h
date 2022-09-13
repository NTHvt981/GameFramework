#pragma once
#include "Core/DataTypes/String.h"
#include <stdint.h>

namespace xml
{

template<typename T>
struct XmlDataType
{
	virtual data_types::String GetKey() = 0;
};

struct XmlStringDataType: XmlDataType<data_types::String>
{
	data_types::String GetKey() override
	{
		return "string";
	}
};

} // namespace xml
