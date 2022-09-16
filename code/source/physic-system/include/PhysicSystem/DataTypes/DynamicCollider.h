#pragma once
#include "Collider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Helpers/BoxHelper.h"

namespace physics
{

struct DynamicCollider : public Collider
{
	data_types::BoxF RelativeBoundary;
	data_types::Vector2F Position;
	data_types::BoxF GetBoundary() const override
	{
		return RelativeBoundary + Position;
	}
};

} // namespace physics