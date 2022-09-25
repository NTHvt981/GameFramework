#pragma once
#include "Collider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Helpers/BoxVector2Helper.h"

namespace physics
{

struct DynamicCollider : public Collider
{
	using Collider::Collider;

	core::BoxF RelativeBoundary;
	core::Vector2F Position;
	core::BoxF GetBoundary() const override
	{
		return RelativeBoundary + Position;
	}

	signals::Signal<core::EntityId> sig_onEntityCollide;
};

} // namespace physics