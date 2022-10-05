#pragma once
#include <cstdint>

namespace core
{

enum class ScriptState : uint64_t
{
	Created,
	Active,
	Paused,
	Inactive,
	Resumed,
	Destroyed
};

} // namespace core