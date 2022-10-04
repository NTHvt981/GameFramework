#pragma once
#include <cstdint>

namespace core
{

enum class ScriptState : uint64_t
{
	OnCreated,
	OnGoing,
	OnPaused,
	OnResumed,
	OnDestroyed
};

} // namespace core