#include "PhysicSystem/PhysicSystem.h"
#include "CollisionHelper.h"
#include "Core/Helpers/Vector2Helper.h"
#include "Core/Math/Math.h"

namespace physics
{

PhysicSystem::PhysicSystem(std::weak_ptr<core::logic::IGameClock> i_gameClock)
{
	std::shared_ptr<core::logic::IGameClock> gameClock = i_gameClock.lock();
	m_onPreFixedUpdateCon = gameClock->sig_onPreRender.Connect(std::bind(&PhysicSystem::OnPreFixedUpdate, this, std::placeholders::_1));
	m_onFixedUpdateCon = gameClock->sig_onRender.Connect(std::bind(&PhysicSystem::OnFixedUpdate, this, std::placeholders::_1));
	m_onPostFixedUpdateCon = gameClock->sig_onPostRender.Connect(std::bind(&PhysicSystem::OnPostFixedUpdate, this, std::placeholders::_1));
}

void PhysicSystem::Initialize()
{
}

void PhysicSystem::Shutdown()
{
}

void PhysicSystem::RegisterDynamicCollider(core::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider)
{
	assert(!m_colliders.contains(i_entityId));
	assert(!m_dynamicColliders.contains(i_entityId));

	std::shared_ptr<DynamicCollider> colliderSharedPtr = i_collider.lock();
	m_colliders.emplace(i_entityId, colliderSharedPtr);
	m_dynamicColliders.emplace(i_entityId, colliderSharedPtr);
}

void PhysicSystem::DeregisterDynamicCollider(core::EntityId i_entityId)
{
	assert(m_colliders.contains(i_entityId));
	assert(m_dynamicColliders.contains(i_entityId));

	m_dynamicColliders[i_entityId].reset();
	m_colliders[i_entityId].reset();
}

void PhysicSystem::RegisterStaticCollider(core::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider)
{
	assert(!m_colliders.contains(i_entityId));
	assert(!m_staticColliders.contains(i_entityId));

	std::shared_ptr<StaticCollider> colliderSharedPtr = i_collider.lock();
	m_colliders.emplace(i_entityId, colliderSharedPtr);
	m_staticColliders.emplace(i_entityId, colliderSharedPtr);
}

void PhysicSystem::DeregisterStaticCollider(core::EntityId i_entityId)
{
	assert(m_colliders.contains(i_entityId));
	assert(m_staticColliders.contains(i_entityId));

	m_staticColliders[i_entityId].reset();
	m_colliders[i_entityId].reset();
}

PhysicSystem::CalculatePosition PhysicSystem::CheckMove(core::EntityId i_selfEntityId, const core::Vector2F& i_velocity)
{
	std::shared_ptr<const DynamicCollider> selfCollider = m_dynamicColliders[i_selfEntityId].lock();
	core::Vector2F selfPosition = selfCollider->Position;
	core::Vector2F resultVelocity = i_velocity;

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
			core::Vector2F newVelocity = newPosition - selfPosition;

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

void PhysicSystem::SetCollisionCheckFilter(const core::BoxI64 i_boundary)
{
	m_filterBound = i_boundary;
}

void PhysicSystem::RemoveCollisionCheckFilter()
{
	m_filterBound.reset();
}

void PhysicSystem::UpdateDynamicColliderState(UpdateDynamicColliderStateParam param) const
{
	const core::EntityId selfEntityId = param.entityId;
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

void PhysicSystem::OnPreFixedUpdate(const uint64_t dt)
{
}

void PhysicSystem::OnFixedUpdate(const uint64_t dt)
{
}

void PhysicSystem::OnPostFixedUpdate(const uint64_t dt)
{
}

bool PhysicSystem::CheckFilter(const core::BoxI64 i_renderBoundary) const
{
	if (m_filterBound.has_value())
	{
		const core::BoxI64& filterBound = m_filterBound.value();
		return core::IsOverlap(i_renderBoundary, filterBound);
	}
	return true;
}

} // namespace physics