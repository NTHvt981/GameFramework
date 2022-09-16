#pragma once
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Vector2.h"

namespace physics
{

namespace helper
{

struct CheckCollideResult
{
	float collideTime;
	data_types::Vector2F collideDirection;
	bool IsCollide() const;
};

CheckCollideResult CheckCollide(
	const data_types::BoxF i_move,
	const data_types::Vector2F i_moveVelocity,
	const data_types::BoxF i_static
);

data_types::BoxF GetBroadphaseBox(
	const data_types::BoxF i_move,
	const data_types::Vector2F i_moveVelocity
);

bool CheckOverlap(
	const data_types::BoxF i_boxA,
	const data_types::BoxF i_boxB
);

using NewPosition = data_types::Vector2F;
NewPosition CalculateDeflect(
	const data_types::Vector2F i_oldPosition,
	const data_types::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculatePush(
	const data_types::Vector2F i_oldPosition,
	const data_types::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculateSlide(
	const data_types::Vector2F i_oldPosition,
	const data_types::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

NewPosition CalculateStop(
	const data_types::Vector2F i_oldPosition,
	const data_types::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult
);

} // namespace helper

} // namespace physics