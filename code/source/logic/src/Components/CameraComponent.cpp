#include "Logic/Components/CameraComponent.h"

namespace logic
{

CameraComponent::CameraComponent(
	std::shared_ptr<camera::IEntityCameraAPI> i_cameraAPI,
	core::EntityId i_entityId)
	: m_cameraAPI(core::Ref<camera::IEntityCameraAPI>(i_cameraAPI))
	, m_entityId(i_entityId)
{
}

void CameraComponent::Register()
{
	m_cameraAPI->RegisterCameraControl(m_entityId);
}

void CameraComponent::Deregister()
{
	m_cameraAPI->DeregisterCameraControl(m_entityId);
}

void CameraComponent::SetPosition(core::Vector2F i_position)
{
	m_position = i_position;
}

core::Vector2F CameraComponent::GetPosition() const
{
	return m_position;
}

void CameraComponent::SetCameraPosition(core::Vector2F i_position)
{
	m_cameraAPI->TrySetPosition(m_entityId, i_position);
}

void CameraComponent::SetCameraSize(core::SizeF i_size)
{
	m_cameraAPI->TrySetSize(m_entityId, i_size);
}

void CameraComponent::SetCameraCentralPosition(core::Vector2F i_position)
{
	m_cameraAPI->TrySetCentralPosition(m_entityId, i_position);
}

} // namespace logic