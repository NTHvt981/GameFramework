#pragma once
#include "ITransformComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Identifiers/CollisionLayer.h"
#include "Core/DataTypes/Size.h"
#include "Core/Signals/Signal.h"
#include <memory>

namespace physics
{
class IPhysicAPI;
struct DynamicCollider;
} // namespace physics

namespace logic
{

static constexpr core::ComponentKey sk_kinematicBodyComponentKey = "KinematicBodyComponent";

class KinematicBodyComponent final: public ITransformComponent
{
public:
	KinematicBodyComponent(
		std::weak_ptr<physics::IPhysicAPI> i_physicAPI,
		core::EntityId i_entityId
	);

	// Inherited via Component
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const;
	void Register() override;
	void Deregister() override;

	using RemainVelocity = core::Vector2F;
	RemainVelocity Move(const core::Vector2F& i_velocity);
	void SetCollisionLayer(const core::CollisionLayer i_collisionLayer);
	void SetColliderSize(const core::SizeF& i_size);

	signals::Signal<core::Vector2F> sig_onMove;
	signals::Signal<core::EntityId> sig_onEntityOverlap;
	signals::Signal<core::EntityId> sig_onEntityCollide;
private:
	void OnEntityOverlap(core::EntityId i_entityId);
	void OnEntityCollide(core::EntityId i_entityId);

	std::weak_ptr<physics::IPhysicAPI> m_physicAPI;
	std::shared_ptr<physics::DynamicCollider> m_dynamicCollider;
	bool isRegistered = false;

	signals::Connection<core::EntityId> m_onEntityOverlapCon;
	signals::Connection<core::EntityId> m_onEntityCollideCon;

	// Inherited via ITransformComponent
};

} // namespace logic