#pragma once
#include "IPhysicSystem.h"
#include "Core/GameClock/IGameClock.h"
#include <map>

namespace physics
{

class PhysicSystem final : public IPhysicSystem
{
public:
	PhysicSystem(std::weak_ptr<core::logic::IGameClock> i_gameClock);

	// Inherited via IPhysicSystem
	void Initialize() override;
	void Shutdown() override;
	void UpdateDynamicColliderStates() const override;

	// Inherited via IPhysicAPI
	void RegisterDynamicCollider(ids::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider) override;
	void DeregisterDynamicCollider(ids::EntityId i_entityId) override;
	void RegisterStaticCollider(ids::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider) override;
	void DeregisterStaticCollider(ids::EntityId i_entityId) override;
	CalculatePosition CheckMove(ids::EntityId i_selfEntityId, const core::Vector2F& i_velocity) override;

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

	// IGameClock funcs
	void OnPreFixedUpdate(const uint64_t dt);
	void OnFixedUpdate(const uint64_t dt);
	void OnPostFixedUpdate(const uint64_t dt);
	signals::Connection<const uint64_t> m_onPreFixedUpdateCon;
	signals::Connection<const uint64_t> m_onFixedUpdateCon;
	signals::Connection<const uint64_t> m_onPostFixedUpdateCon;
};

} // namespace physics