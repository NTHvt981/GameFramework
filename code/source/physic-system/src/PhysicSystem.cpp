#include "PhysicSystem/PhysicSystem.h"
#include "CollisionHelper.h"
#include "Core/Helpers/Vector2Helper.h"
#include "Core/Math/Math.h"

namespace physics
{

PhysicSystem::PhysicSystem()
{
}

void PhysicSystem::Initialize()
{
}

void PhysicSystem::Shutdown()
{
}

void PhysicSystem::PreFixedUpdate(const uint64_t dt)
{
}

void PhysicSystem::FixedUpdate(const uint64_t dt)
{
}

void PhysicSystem::PostFixedUpdate(const uint64_t dt)
{
	UpdateDynamicColliderOverlapStates();
}

void PhysicSystem::RegisterCollider(std::shared_ptr<DynamicCollider> i_collider)
{
	i_collider->id = m_idGenerator.Generate();
	m_colliders.emplace(i_collider->id, i_collider);
	m_dynamicColliders.emplace(i_collider->id, i_collider);
}

void PhysicSystem::RegisterCollider(std::shared_ptr<StaticCollider> i_collider)
{
	i_collider->id = m_idGenerator.Generate();
	m_colliders.emplace(i_collider->id, i_collider);
	m_staticColliders.emplace(i_collider->id, i_collider);
}

void PhysicSystem::DeregisterCollider(Collider::Id id)
{
	if (m_staticColliders.contains(id))
	{
		m_staticColliders[id].reset();
	}
	if (m_dynamicColliders.contains(id))
	{
		m_dynamicColliders[id].reset();
	}
	m_colliders[id].reset();
}

PhysicSystem::NewPosition PhysicSystem::CheckMove(
	Collider::Id i_colliderId, 
	const core::Vector2F& i_velocity, 
	bool i_emitSignal)
{
	std::shared_ptr<const DynamicCollider> moveCollider = m_dynamicColliders[i_colliderId].lock();
	core::Vector2F movePosition = moveCollider->Position;
	core::Vector2F resultVelocity = i_velocity;

	for (const auto& [staticColliderId, staticCollider] : m_colliders)
	{
		if (!CheckCollideOtherConditions(moveCollider, staticCollider))
		{
			continue;
		}

		const helper::CheckCollideResult result = helper::CheckCollide(
			moveCollider->GetBoundary(),
			resultVelocity,
			staticCollider->GetBoundary()
		);

		if (result.IsCollide())
		{
			const helper::NewPosition newPosition = helper::CalculateStop(movePosition, resultVelocity, result);
			core::Vector2F newVelocity = newPosition - movePosition;

			resultVelocity = core::GetNearestZero(resultVelocity, newVelocity);

			if (i_emitSignal)
			{
				moveCollider->sig_onEntityCollide.Emit(staticCollider->entityId);
			}
		}
	}

	return movePosition + resultVelocity;
}

void PhysicSystem::UpdateDynamicColliderOverlapStates() const
{
	for (const auto& [entityId, collider] : m_colliders)
	{
		UpdateDynamicColliderOverlapState(collider);
	}
}

void PhysicSystem::SetCollisionCheckFilter(const core::BoxF i_boundary)
{
	m_collisionFilter = i_boundary;
}

void PhysicSystem::RemoveCollisionCheckFilter()
{
	m_collisionFilter.reset();
}

void PhysicSystem::UpdateDynamicColliderOverlapState(std::shared_ptr<const Collider> collider) const
{
	for (const auto& [otherEntityId, otherCollider] : m_colliders)
	{
		if (!CheckOverlapOtherConditions(collider, otherCollider))
		{
			continue;
		}

		const bool IsOverlap = core::IsOverlap(collider->GetBoundary(), otherCollider->GetBoundary());

		if (IsOverlap && CheckCollideOtherConditions(collider, otherCollider))
		{
			collider->sig_onEntityOverlap.Emit(otherCollider->entityId);
			otherCollider->sig_onEntityOverlap.Emit(collider->entityId);
		}
	}
}

bool PhysicSystem::CheckCollideOtherConditions(
	std::shared_ptr<const Collider> i_moveCollider,
	std::shared_ptr<const Collider> i_staticCollider) const
{
	const bool isASolid = i_moveCollider->isSolid;
	const bool isBSolid = i_staticCollider->isSolid;
	return CheckOverlapOtherConditions(i_moveCollider, i_staticCollider) &&
		(isASolid || isBSolid);
}

bool PhysicSystem::CheckOverlapOtherConditions(
	std::shared_ptr<const Collider> i_colliderA,
	std::shared_ptr<const Collider> i_colliderB) const
{
	const bool sameCollider = i_colliderA->id == i_colliderB->id;
	const bool sameOwner = i_colliderA->entityId == i_colliderB->entityId;
	return !(sameCollider || sameOwner);
}

bool PhysicSystem::CheckCollisionFilter(std::shared_ptr<const Collider> i_collider) const
{
	if (m_collisionFilter.has_value())
	{
		const core::BoxF& filterBound = m_collisionFilter.value();
		return core::IsOverlap(i_collider->GetBoundary(), filterBound);
	}
	return true;
}

} // namespace physics