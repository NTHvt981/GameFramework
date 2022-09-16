#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/Signals/Signal.h"
#include "Core/Identifiers/EntityId.h"

namespace physics
{

struct Collider
{
	virtual data_types::BoxF GetBoundary() const = 0;
};

} // namespace physics