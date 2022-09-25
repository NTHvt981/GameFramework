#pragma once
#include "Generator.h"
#include <stdint.h>

namespace core
{

class IncrementIdGenerator final: public Generator<uint64_t>
{
public:
	IncrementIdGenerator(uint64_t i_startingId = 0);
	uint64_t Generate() override;

private:
	uint64_t m_currentId;
};


} // namespace core