#pragma once
#include <stdint.h>
#include <minwindef.h>

namespace core
{

class IUpdateable
{
	virtual void Update(uint64_t i_timeElapsed) = 0;
};

} // namespace ideps