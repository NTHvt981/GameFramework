#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Identifiers/CollisionLayer.h"

namespace physics
{

namespace helper
{

struct CheckCollideResult
{
	float collideTime;
	core::Vector2F collideDirection;
	bool IsCollide() const;
};

CheckCollideResult CheckCollide(
	const core::BoxF i_move,
	const core::Vector2F i_moveVelocity,
	const core::BoxF i_static
);

core::BoxF GetBroadphaseBox(
	const core::BoxF i_move,
	const core::Vector2F i_moveVelocity
);

bool CheckOverlap(
	const core::BoxF i_boxA,
	const core::BoxF i_boxB
);

using NewPosition = core::Vector2F;
NewPosition CalculateDeflect(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculatePush(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculateSlide(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculateStop(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

/// <summary>
/// Note: param order is important
/// </summary>
bool CheckCollisionLayerCondition(
	const core::CollisionLayer i_moveLayer,
	const core::CollisionLayer i_staticLayer
);

} // namespace helper

} // namespace physics