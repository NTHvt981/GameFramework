#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/Signals/Signal.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Identifiers/CollisionLayer.h"

namespace physics
{

struct Collider
{
	Collider(const core::EntityId i_entityId)
		: entityId(i_entityId)
	{

	}

	using Id = uint64_t;
	Id id = UINT64_MAX;
	const core::EntityId entityId;
	core::CollisionLayer collisionLayer = core::CollisionLayer::Default;

	virtual core::BoxF GetBoundary() const = 0;

	signals::Signal<core::EntityId> sig_onEntityOverlap;
};

} // namespace physics