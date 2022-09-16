#pragma once
#include "Collider.h"

namespace physics
{

struct StaticCollider: public Collider
{
	data_types::BoxF AbsoluteBoundary;
	data_types::BoxF GetBoundary() const override
	{
		return AbsoluteBoundary;
	}
};

} // namespace physics