#pragma once
#include "IPhysicSystem.h"
#include "Core/GameClock/IGameClock.h"
#include <map>
#include <optional>

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
	void SetCollisionCheckFilter(const core::BoxI64 i_boundary) override;
	void RemoveCollisionCheckFilter() override;

	// Inherited via IPhysicAPI
	void RegisterDynamicCollider(core::EntityId i_entityId, std::weak_ptr<DynamicCollider> i_collider) override;
	void DeregisterDynamicCollider(core::EntityId i_entityId) override;
	void RegisterStaticCollider(core::EntityId i_entityId, std::weak_ptr<StaticCollider> i_collider) override;
	void DeregisterStaticCollider(core::EntityId i_entityId) override;
	CalculatePosition CheckMove(core::EntityId i_selfEntityId, const core::Vector2F& i_velocity) override;

private:
	struct UpdateDynamicColliderStateParam
	{
		const core::EntityId entityId;
		std::shared_ptr<const Collider> collider;
	};
	void UpdateDynamicColliderState(UpdateDynamicColliderStateParam param) const;

	std::map<core::EntityId, std::shared_ptr<Collider>> m_colliders;
	std::map<core::EntityId, std::weak_ptr<DynamicCollider>> m_dynamicColliders;
	std::map<core::EntityId, std::weak_ptr<StaticCollider>> m_staticColliders;

	// IGameClock funcs
	void OnPreFixedUpdate(const uint64_t dt);
	void OnFixedUpdate(const uint64_t dt);
	void OnPostFixedUpdate(const uint64_t dt);
	signals::Connection<const uint64_t> m_onPreFixedUpdateCon;
	signals::Connection<const uint64_t> m_onFixedUpdateCon;
	signals::Connection<const uint64_t> m_onPostFixedUpdateCon;

	bool CheckFilter(const core::BoxI64 i_renderBoundary) const;
	std::optional<core::BoxI64> m_filterBound;
};

} // namespace physics