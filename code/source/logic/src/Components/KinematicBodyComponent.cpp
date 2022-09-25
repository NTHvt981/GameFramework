#include "Logic/Components/KinematicBodyComponent.h"
#include "Core/Helpers/Vector2Helper.h"

namespace logic
{

KinematicBodyComponent::KinematicBodyComponent(
	std::weak_ptr<physics::IPhysicAPI> i_physicAPI, 
	std::shared_ptr<physics::DynamicCollider> i_dynamicCollider)
	: m_physicAPI(i_physicAPI)
	, m_dynamicCollider(i_dynamicCollider)
{
}

void KinematicBodyComponent::SetPosition(const core::Vector2F& i_position)
{
	m_dynamicCollider->Position = i_position;
}

core::Vector2F KinematicBodyComponent::GetPosition() const
{
	return m_dynamicCollider->Position;
}

void KinematicBodyComponent::Register()
{
	if (isRegistered)
	{
		return;
	}
	isRegistered = true;

	m_physicAPI.lock()->RegisterCollider(m_dynamicCollider);
}

void KinematicBodyComponent::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	m_physicAPI.lock()->DeregisterCollider(m_dynamicCollider->id);
}

KinematicBodyComponent::RemainVelocity KinematicBodyComponent::Move(const core::Vector2F& i_velocity)
{
	const bool requestEmitSignal = true;
	core::Vector2F newPosition = m_physicAPI.lock()->CheckMove(m_dynamicCollider->id, i_velocity, requestEmitSignal);
	RemainVelocity result = newPosition - GetPosition();
	SetPosition(newPosition);
	return result;
}

} // namespace logic