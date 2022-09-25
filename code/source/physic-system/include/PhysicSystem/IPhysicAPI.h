#pragma once
#include <memory>
#include "DataTypes/Collider.h"
#include "DataTypes/DynamicCollider.h"
#include "DataTypes/StaticCollider.h"
#include "Core/DataTypes/Vector2.h"

namespace physics
{

class IPhysicAPI
{
public:
	virtual void RegisterCollider(std::shared_ptr<DynamicCollider> i_collider) = 0;
	virtual void RegisterCollider(std::shared_ptr<StaticCollider> i_collider) = 0;
	virtual void DeregisterCollider(Collider::Id id) = 0;
	using NewPosition = core::Vector2F;
	virtual NewPosition CheckMove(Collider::Id id, const core::Vector2F& i_velocity, bool i_emitSignal = false) = 0;
};

} // namespace physics