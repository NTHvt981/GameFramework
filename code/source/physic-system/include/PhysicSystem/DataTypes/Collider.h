#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/Signals/Signal.h"
#include "Core/Identifiers/EntityId.h"

namespace physics
{

struct Collider
{
	using Id = uint64_t;
	Id id;
	const core::EntityId entityId;
	bool isSolid;

	virtual core::BoxF GetBoundary() const = 0;

	signals::Signal<core::EntityId> sig_onEntityOverlap;
};

} // namespace physics