#pragma once
#include "Core/APIs/IPhysicAPI.h"
#include "Core/Generator/IncrementIdGenerator.h"
#include "Core/DataTypes/Duration.h"
#include <map>
#include <optional>

namespace logic
{

class PhysicSystem final : public core::IPhysicAPI
{
public:
	PhysicSystem();

	void Initialize();
	void Shutdown();

	void SetCollisionCheckFilter(const core::BoxF i_boundary);
	void RemoveCollisionCheckFilter();

	void Update(const core::Duration& dt);

	void RegisterCollider(std::shared_ptr<core::DynamicCollider> i_collider) override;
	void RegisterCollider(std::shared_ptr<core::StaticCollider> i_collider) override;
	void DeregisterCollider(core::Collider::Id id) override;
	NewPosition CheckMove(core::Collider::Id i_colliderId, const core::Vector2F& i_velocity, bool i_emitSignal) override;

private:
	void UpdateDynamicColliderOverlapStates() const;
	void UpdateDynamicColliderOverlapState(std::shared_ptr<const core::Collider> collider) const;
	bool CheckCollideOtherConditions(
		std::shared_ptr<const core::Collider> i_moveCollider,
		std::shared_ptr<const core::Collider> i_staticCollider
	) const;
	bool CheckOverlapOtherConditions(
		std::shared_ptr<const core::Collider> i_colliderA,
		std::shared_ptr<const core::Collider> i_colliderB
	) const;

	std::map<core::Collider::Id, std::shared_ptr<core::Collider>> m_colliders;
	std::map<core::Collider::Id, std::weak_ptr<core::DynamicCollider>> m_dynamicColliders;
	std::map<core::Collider::Id, std::weak_ptr<core::StaticCollider>> m_staticColliders;
	core::IncrementIdGenerator m_idGenerator;

	bool CheckCollisionFilter(std::shared_ptr<const core::Collider> i_collider) const;
	std::optional<core::BoxF> m_collisionFilter;
};

} // namespace logic