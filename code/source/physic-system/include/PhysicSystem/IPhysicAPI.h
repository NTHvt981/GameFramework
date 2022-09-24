#pragma once
#include <memory>
#include "DataTypes/Collider.h"
#include "DataTypes/DynamicCollider.h"
#include "DataTypes/StaticCollider.h"
#include "Core/DataTypes/Vector2.h"
#include "Core/Identifiers/EntityId.h"

namespace physics
{

class IPhysicAPI
{
public:
	using CalculatePosition = core::Vector2F;
	virtual void RegisterDynamicCollider(core::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider) = 0;
	virtual void DeregisterDynamicCollider(core::EntityId i_entityId) = 0;
	virtual void RegisterStaticCollider(core::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider) = 0;
	virtual void DeregisterStaticCollider(core::EntityId i_entityId) = 0;
	virtual CalculatePosition CheckMove(core::EntityId i_selfEntityId, const core::Vector2F& i_velocity) = 0;
};

} // namespace physics