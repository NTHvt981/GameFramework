#pragma once
#include "PositionSetterComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Signals/Signal.h"
#include "PhysicSystem/DataTypes/DynamicCollider.h"
#include "PhysicSystem/IPhysicAPI.h"
#include <memory>

namespace logic
{

/// <summary>
/// Hold dynamic colliders
/// </summary>
class KinematicBodyComponent final: public PositionSetterComponent
{
public:
	KinematicBodyComponent(
		std::weak_ptr<physics::IPhysicAPI> i_physicAPI,
		std::shared_ptr<physics::DynamicCollider> i_dynamicCollider
	);

	// Inherited via Component
	void Register() override;
	void Deregister() override;

	using RemainVelocity = core::Vector2F;
	RemainVelocity Move(const core::Vector2F& i_velocity);
	void SetCollisionLayer(const core::CollisionLayer i_collisionLayer);

	signals::Signal<core::Vector2F> sig_onMove;
	signals::Signal<core::EntityId> sig_onEntityOverlap;
	signals::Signal<core::EntityId> sig_onEntityCollide;
private:
	void OnEntityOverlap(core::EntityId i_entityId);
	void OnEntityCollide(core::EntityId i_entityId);
	void SetPosition(const core::Vector2F& i_position) override;

	std::weak_ptr<physics::IPhysicAPI> m_physicAPI;
	std::shared_ptr<physics::DynamicCollider> m_dynamicCollider;
	bool isRegistered = false;

	signals::Connection<core::EntityId> m_onEntityOverlapCon;
	signals::Connection<core::EntityId> m_onEntityCollideCon;
};

} // namespace logic