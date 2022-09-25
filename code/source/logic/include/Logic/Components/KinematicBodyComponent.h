#pragma once
#include "IComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "PhysicSystem/DataTypes/DynamicCollider.h"
#include "PhysicSystem/IPhysicAPI.h"
#include <memory>

namespace logic
{

/// <summary>
/// Hold dynamic colliders
/// </summary>
class KinematicBodyComponent final: public IComponent
{
public:
	KinematicBodyComponent(
		std::weak_ptr<physics::IPhysicAPI> i_physicAPI,
		std::shared_ptr<physics::DynamicCollider> i_dynamicCollider
	);

	// Inherited via IComponent
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

	using RemainVelocity = core::Vector2F;
	RemainVelocity Move(const core::Vector2F& i_velocity);

private:
	void SetPosition(const core::Vector2F& i_position) override;

	std::weak_ptr<physics::IPhysicAPI> m_physicAPI;
	std::shared_ptr<physics::DynamicCollider> m_dynamicCollider;
	bool isRegistered = false;
};

} // namespace logic