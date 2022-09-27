#pragma once
#include "Collider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Helpers/BoxVector2Helper.h"

namespace physics
{

struct DynamicCollider : public Collider
{
	using Collider::Collider;

	core::BoxF relativeBoundary;
	core::Vector2F position;
	core::BoxF GetBoundary() const override
	{
		return relativeBoundary + position;
	}

	signals::Signal<core::EntityId> sig_onEntityCollide;
};

} // namespace physics