#pragma once
#include "Core/DataTypes/Vector2.h"

namespace logic
{

/// <summary>
/// Every component inherit this class
/// </summary>
class Component
{
public:
	virtual void Register() = 0;
	virtual void Deregister() = 0;
};

} // namespace logic
