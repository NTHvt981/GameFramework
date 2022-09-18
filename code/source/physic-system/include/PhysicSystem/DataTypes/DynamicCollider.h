#pragma once
#include "Collider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Helpers/BoxHelper.h"

namespace physics
{

struct DynamicCollider : public Collider
{
	core::BoxF RelativeBoundary;
	core::Vector2F Position;
	core::BoxF GetBoundary() const override
	{
		return RelativeBoundary + Position;
	}
};

} // namespace physics