#pragma once
#include "IPhysicSystem.h"
#include <map>

namespace physics
{

class PhysicSystem final : public IPhysicSystem
{
public:
	// Inherited via IPhysicSystem
	void Initialize() override;
	void Shutdown() override;
	void UpdateDynamicColliderStates() const override;

	// Inherited via IPhysicAPI
	void RegisterDynamicCollider(ids::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider) override;
	void DeregisterDynamicCollider(ids::EntityId i_entityId) override;
	void RegisterStaticCollider(ids::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider) override;
	void DeregisterStaticCollider(ids::EntityId i_entityId) override;
	CalculatePosition CheckMove(ids::EntityId i_selfEntityId, const data_types::Vector2F& i_velocity) override;

private:
	struct UpdateDynamicColliderStateParam
	{
		const ids::EntityId entityId;
		std::shared_ptr<const Collider> collider;
	};
	void UpdateDynamicColliderState(UpdateDynamicColliderStateParam param) const;

	std::map<ids::EntityId, std::shared_ptr<Collider>> m_colliders;
	std::map<ids::EntityId, std::weak_ptr<DynamicCollider>> m_dynamicColliders;
	std::map<ids::EntityId, std::weak_ptr<StaticCollider>> m_staticColliders;
};

} // namespace physics