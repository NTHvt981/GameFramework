#include "PhysicSystem/PhysicSystem.h"
#include "CollisionHelper.h"
#include "Core/Helpers/Vector2Helper.h"

namespace physics
{

void PhysicSystem::Initialize()
{
}

void PhysicSystem::Shutdown()
{
}

void PhysicSystem::RegisterDynamicCollider(ids::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider)
{
	assert(!m_colliders.contains(i_entityId));
	assert(!m_dynamicColliders.contains(i_entityId));

	std::shared_ptr<DynamicCollider> colliderSharedPtr = i_collider.lock();
	m_colliders.emplace(i_entityId, colliderSharedPtr);
	m_dynamicColliders.emplace(i_entityId, colliderSharedPtr);
}

void PhysicSystem::DeregisterDynamicCollider(ids::EntityId i_entityId)
{
	assert(m_colliders.contains(i_entityId));
	assert(m_dynamicColliders.contains(i_entityId));

	m_dynamicColliders[i_entityId].reset();
	m_colliders[i_entityId].reset();
}

void PhysicSystem::RegisterStaticCollider(ids::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider)
{
	assert(!m_colliders.contains(i_entityId));
	assert(!m_staticColliders.contains(i_entityId));

	std::shared_ptr<StaticCollider> colliderSharedPtr = i_collider.lock();
	m_colliders.emplace(i_entityId, colliderSharedPtr);
	m_staticColliders.emplace(i_entityId, colliderSharedPtr);
}

void PhysicSystem::DeregisterStaticCollider(ids::EntityId i_entityId)
{
	assert(m_colliders.contains(i_entityId));
	assert(m_staticColliders.contains(i_entityId));

	m_staticColliders[i_entityId].reset();
	m_colliders[i_entityId].reset();
}

PhysicSystem::CalculatePosition PhysicSystem::CheckMove(ids::EntityId i_selfEntityId, const data_types::Vector2F& i_velocity)
{
	std::shared_ptr<const DynamicCollider> selfCollider = m_dynamicColliders[i_selfEntityId].lock();
	data_types::Vector2F selfPosition = selfCollider->Position;
	data_types::Vector2F resultVelocity = i_velocity;

	for (const auto& [otherEntityId, otherCollider] : m_colliders)
	{
		if (i_selfEntityId == otherEntityId)
		{
			continue;
		}

		const helper::CheckCollideResult result = helper::CheckCollide(
			selfCollider->GetBoundary(),
			resultVelocity,
			otherCollider->GetBoundary()
		);

		if (result.IsCollide())
		{
			sig_onEntityCollide.Emit(i_selfEntityId, otherEntityId);

			const helper::NewPosition newPosition = helper::CalculateStop(selfPosition, resultVelocity, result);
			data_types::Vector2F newVelocity = newPosition - selfPosition;

			if (std::abs(resultVelocity.x) < std::abs(newVelocity.x))
			{
				resultVelocity.x = newVelocity.x;
			}

			if (std::abs(resultVelocity.y) < std::abs(newVelocity.y))
			{
				resultVelocity.y = newVelocity.y;
			}
		}
	}

	return selfPosition + resultVelocity;
}

void PhysicSystem::UpdateDynamicColliderStates() const
{
	for (const auto& [entityId, collider] : m_dynamicColliders)
	{
		UpdateDynamicColliderState(UpdateDynamicColliderStateParam
			{
				entityId,
				collider.lock()
			}
		);
	}
}

void PhysicSystem::UpdateDynamicColliderState(UpdateDynamicColliderStateParam param) const
{
	const ids::EntityId selfEntityId = param.entityId;
	std::shared_ptr<const Collider> selfCollider = param.collider;

	for (const auto& [otherEntityId, otherCollider] : m_colliders)
	{
		if (selfEntityId == otherEntityId)
		{
			continue;
		}

		const bool isOverlap = helper::CheckOverlap(selfCollider->GetBoundary(), otherCollider->GetBoundary());
		if (isOverlap)
		{
			sig_onEntityTouch.Emit(selfEntityId, otherEntityId);
		}
	}
}

} // namespace physics