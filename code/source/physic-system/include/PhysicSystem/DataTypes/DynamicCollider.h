#pragma once
#include "Collider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/Size.h"
#include "Core/Helpers/SizeBoxHelper.h"

namespace physics
{

struct DynamicCollider : public Collider
{
	using Collider::Collider;

	core::SizeF size;
	core::Vector2F position;
	core::BoxF GetBoundary() const override
	{
		return position + size;
	}

	signals::Signal<core::EntityId> sig_onEntityCollide;
};

} // namespace physics