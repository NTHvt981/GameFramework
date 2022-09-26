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

void KinematicBodyComponent::OnEntityOverlap(core::EntityId i_entityId)
{
	sig_onEntityOverlap.Emit(i_entityId);
}

void KinematicBodyComponent::OnEntityCollide(core::EntityId i_entityId)
{
	sig_onEntityCollide.Emit(i_entityId);
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

	m_onEntityCollideCon = m_dynamicCollider->sig_onEntityCollide.Connect(
		std::bind(&KinematicBodyComponent::OnEntityCollide, this, std::placeholders::_1)
	);
	m_onEntityOverlapCon = m_dynamicCollider->sig_onEntityOverlap.Connect(
		std::bind(&KinematicBodyComponent::OnEntityOverlap, this, std::placeholders::_1)
	);
}

void KinematicBodyComponent::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	m_physicAPI.lock()->DeregisterCollider(m_dynamicCollider->id);

	m_onEntityOverlapCon.Disconnect();
	m_onEntityCollideCon.Disconnect();
}

KinematicBodyComponent::RemainVelocity KinematicBodyComponent::Move(const core::Vector2F& i_velocity)
{
	const bool requestEmitSignal = true;
	core::Vector2F newPosition = m_physicAPI.lock()->CheckMove(m_dynamicCollider->id, i_velocity, requestEmitSignal);
	
	RemainVelocity result = newPosition - GetPosition();
	SetPosition(newPosition);
	sig_onMove.Emit(newPosition);
	return result;
}

void KinematicBodyComponent::SetCollisionLayer(const core::CollisionLayer i_collisionLayer)
{
	m_dynamicCollider->collisionLayer = i_collisionLayer;
}

} // namespace logic