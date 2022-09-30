#pragma once
#include "Core/Identifiers/ComponentKey.h"

namespace logic
{

/// <summary>
/// Every component inherit this class
/// </summary>
class IComponent
{
public:
	virtual void Register() = 0;
	virtual void Deregister() = 0;
};

} // namespace logic
