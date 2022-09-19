#pragma once
#include "Core/DataTypes/Size.h"
#include "Core/DataTypes/String.h"

namespace core
{

struct GameSetting
{
	SizeI64 windowSize = { 800, 600 };
	String windowTitle = "Test";
	uint64_t frameRate = 60;

	uint64_t GetMillisecondsPerFrame() const
	{
		return 1000 / frameRate;
	}
};

} // namespace core