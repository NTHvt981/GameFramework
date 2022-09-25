#pragma once
#include "IPhysicSystem.h"
#include "Core/Generator/IncrementIdGenerator.h"
#include <map>
#include <optional>

namespace physics
{

class PhysicSystem final : public IPhysicSystem
{
public:
	PhysicSystem();

	// Inherited via IPhysicSystem
	void Initialize() override;
	void Shutdown() override;

	void SetCollisionCheckFilter(const core::BoxF i_boundary) override;
	void RemoveCollisionCheckFilter() override;

	void PreFixedUpdate(const uint64_t dt) override;
	void FixedUpdate(const uint64_t dt) override;
	void PostFixedUpdate(const uint64_t dt) override;

	// Inherited via IPhysicAPI
	void RegisterCollider(std::shared_ptr<DynamicCollider> i_collider) override;
	void RegisterCollider(std::shared_ptr<StaticCollider> i_collider) override;
	void DeregisterCollider(Collider::Id id) override;
	NewPosition CheckMove(Collider::Id i_colliderId, const core::Vector2F& i_velocity, bool i_emitSignal) override;

private:
	void UpdateDynamicColliderOverlapStates() const;
	void UpdateDynamicColliderOverlapState(std::shared_ptr<const Collider> collider) const;
	bool CheckCollideOtherConditions(
		std::shared_ptr<const Collider> i_moveCollider,
		std::shared_ptr<const Collider> i_staticCollider
	) const;
	bool CheckOverlapOtherConditions(
		std::shared_ptr<const Collider> i_colliderA,
		std::shared_ptr<const Collider> i_colliderB
	) const;

	std::map<Collider::Id, std::shared_ptr<Collider>> m_colliders;
	std::map<Collider::Id, std::weak_ptr<DynamicCollider>> m_dynamicColliders;
	std::map<Collider::Id, std::weak_ptr<StaticCollider>> m_staticColliders;
	core::IncrementIdGenerator m_idGenerator;

	bool CheckCollisionFilter(std::shared_ptr<const Collider> i_collider) const;
	std::optional<core::BoxF> m_collisionFilter;
};

} // namespace physics