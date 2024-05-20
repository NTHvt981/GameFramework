#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/Signals/Signal.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Identifiers/CollisionLayer.h"

namespace core
{

struct Collider
{
	Collider(const EntityId i_entityId)
		: entityId(i_entityId)
	{

	}

	using Id = uint64_t;
	Id id = UINT64_MAX;
	const EntityId entityId;
	CollisionLayer collisionLayer = CollisionLayer::Default;

	virtual core::BoxF GetBoundary() const = 0;

	signals::Signal<EntityId> sig_onEntityOverlap;
};

} // namespace core