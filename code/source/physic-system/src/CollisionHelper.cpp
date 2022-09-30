#include "CollisionHelper.h"
#include "Core/Math/Math.h"
#include "Core/Helpers/Vector2Helper.h"
#include <map>

namespace physics
{

namespace helper
{

bool CheckCollideResult::IsCollide() const
{
	return collideDirection == core::Vector2F();
}

CheckCollideResult CheckCollide(
	const core::BoxF i_move,
	const core::Vector2F i_moveVelocity,
	const core::BoxF i_static)
{
	core::Vector2F entry;
	core::Vector2F exit;

	//	what is entryand exit, look at this
	//	move_l		 move_r	   static_l			static_r
	//	| move		|			|	 static |
	//	< -- - entry--->
	//	<------------------ - exit-------------------->
	//	this illustrate the horizontal axis
	//	the same can be said for the vertical axis

	if (i_moveVelocity.x > 0.0f)
	{
		entry.x = i_static.left - i_move.right;
		exit.x = i_static.right - i_move.left;
	}
	else
	{
		entry.x = i_static.right - i_move.left;
		exit.x = i_static.left - i_move.right;
	}

	if (i_moveVelocity.y > 0.0f)
	{
		entry.y = i_static.top - i_move.bottom;
		exit.y = i_static.bottom - i_move.top;
	}
	else
	{
		entry.y = i_static.bottom - i_move.top;
		exit.y = i_static.top - i_move.bottom;
	}

	// find time of collision and time of leaving for
	// each axis(if statement is to prevent divide by zero)
	core::Vector2F entryTimeVector;
	core::Vector2F exitTimeVector;

	//we will devide entry position to velocity to get the entry time
	//for x entry_x / velocity_x
	//what if velocity == 0 ? asign entry time to infinity
	//the same goes for exit time, exit position
	if (i_moveVelocity.x == 0.0f)
	{
		entryTimeVector.x = -std::numeric_limits<float>::infinity();
		exitTimeVector.x = std::numeric_limits<float>::infinity();
	}
	else
	{
		entryTimeVector.x = entry.x / i_moveVelocity.x;
		exitTimeVector.x = exit.x / i_moveVelocity.x;
	}

	if (i_moveVelocity.y == 0.0f)
	{
		entryTimeVector.y = -std::numeric_limits<float>::infinity();
		exitTimeVector.y = std::numeric_limits<float>::infinity();
	}
	else
	{
		entryTimeVector.y = entry.y / i_moveVelocity.y;
		exitTimeVector.y = exit.y / i_moveVelocity.y;
	}

	float entryTime = std::max(entryTimeVector.x, entryTimeVector.y);
	float exitTime = std::min(exitTimeVector.x, exitTimeVector.y);

	// if there was no collision
	if (entryTime > exitTime ||
		entryTimeVector.x < 0.0f && entryTimeVector.y < 0.0f ||
		entryTimeVector.x > 1.0f || entryTimeVector.y > 1.0f)
		//collide time return 0 -> no collision
	{
		return CheckCollideResult
		{
			1.0f,
			core::Vector2F{0.0f, 0.0f}
		};
	}
	else //I dont understand these line
	{
		if (entryTimeVector.x > entryTimeVector.y)
		{
			return CheckCollideResult
			{
				entryTime,
				core::Vector2F{-core::Sign(entry.x), 0.0f}
			};
		}
		else
		{
			return CheckCollideResult
			{
				entryTime,
				core::Vector2F{0.0f, -core::Sign(entry.y)}
			};
		}
	}
}

core::BoxF GetBroadphaseBox(
	const core::BoxF i_move,
	const core::Vector2F i_moveVelocity)
{
	core::BoxF result;

	if (i_moveVelocity.x > 0)
	{
		result.left = i_move.left;
		result.right = i_move.right + i_moveVelocity.x;
	}
	else
	{
		result.left = i_move.left + i_moveVelocity.x;
		result.right = i_move.right;
	}

	if (i_moveVelocity.y > 0)
	{
		result.top = i_move.top;
		result.bottom = i_move.bottom + i_moveVelocity.y;
	}
	else
	{
		result.top = i_move.top + i_moveVelocity.y;
		result.bottom = i_move.bottom;
	}

	return result;
}

bool CheckOverlap(
	const core::BoxF i_boxA,
	const core::BoxF i_boxB)
{
	return (
		i_boxA.right <= i_boxB.left ||
		i_boxB.right <= i_boxA.left ||
		i_boxA.bottom <= i_boxB.top ||
		i_boxB.bottom <= i_boxA.top
		) == false;
}

core::Vector2F CalculateDeflect(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult)
{
	NewPosition result = CalculateStop(i_oldPosition, i_oldVelocity, i_collideResult);

	float remainTime = 1 - i_collideResult.collideTime;
	core::Vector2F newVelocity = i_oldVelocity * remainTime;
	core::Vector2F direction = i_collideResult.collideDirection;

	if (fabsf(direction.x) > 0.0001f)
	{
		newVelocity.x = -newVelocity.x;
	}
	if (fabsf(direction.y) > 0.0001f)
	{
		newVelocity.y = -newVelocity.y;
	}

	return result;
}

NewPosition CalculatePush(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult)
{
	NewPosition result = CalculateStop(i_oldPosition, i_oldVelocity, i_collideResult);

	float remainTime = 1 - i_collideResult.collideTime;
	core::Vector2F direction = i_collideResult.collideDirection;

	float dotProduct = (i_oldVelocity.x * direction.y + i_oldVelocity.y * direction.x);
	if (dotProduct > 0.0f)
	{
		dotProduct = 1.0f;
	}
	else if (dotProduct < 0.0f)
	{
		dotProduct = -1.0f;
	}

	float magnitude = GetLength(i_oldVelocity) * remainTime;
	result = direction * dotProduct * magnitude;

	return result;
}

NewPosition CalculateSlide(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult)
{
	NewPosition result = CalculateStop(i_oldPosition, i_oldVelocity, i_collideResult);

	float remainTime = 1 - i_collideResult.collideTime;
	core::Vector2F direction = i_collideResult.collideDirection;
	//beware v_x * normal_y NOT v_x * normal_x
	float dotProduct = (i_oldVelocity.x * direction.y + i_oldVelocity.y * direction.x) * remainTime;

	const core::Vector2F newVelocity = direction * dotProduct;

	//update position
	result = result + newVelocity;

	return result;
}

NewPosition CalculateStop(
	const core::Vector2F i_oldPosition,
	const core::Vector2F i_oldVelocity,
	const CheckCollideResult i_collideResult)
{
	NewPosition result = i_oldPosition;
	result = result + (i_oldVelocity * i_collideResult.collideTime);

	return result;
}

const std::map<core::CollisionLayer, core::CollisionLayer> sk_mapCollisionLayersInteraction =
{
	{ core::CollisionLayer::Enemy, core::CollisionLayer::Wall },
	{ core::CollisionLayer::Player, core::CollisionLayer::Wall },
	{ core::CollisionLayer::Wall, core::CollisionLayer::Wall },
};

bool CheckCollisionLayerCondition(
	const core::CollisionLayer i_moveLayer,
	const core::CollisionLayer i_staticLayer)
{
	if (!sk_mapCollisionLayersInteraction.contains(i_moveLayer))
	{
		return false;
	}
	return sk_mapCollisionLayersInteraction.at(i_moveLayer) == i_staticLayer;
}

} // namespace helper

} // namespace physics
