#pragma once
#include "Core/Generator/IncrementIdGenerator.h"

namespace core
{

IncrementIdGenerator::IncrementIdGenerator(uint64_t i_startingId)
	: m_currentId(i_startingId)
{
}

uint64_t IncrementIdGenerator::Generate()
{
	m_currentId++;
	return m_currentId;
}

} // namespace core