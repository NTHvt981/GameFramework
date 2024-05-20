#pragma once
#include "Collider.h"

namespace core
{

struct StaticCollider: public Collider
{
	core::BoxF AbsoluteBoundary;
	core::BoxF GetBoundary() const override
	{
		return AbsoluteBoundary;
	}
};

} // namespace physics