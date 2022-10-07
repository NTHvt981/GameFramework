#include "Logic/LogicSystems/CameraSystem/CameraSystem.h"
#include "Core/Helpers/SizeBoxHelper.h"
#include "Core/Macros/Macros.h"
#include <stdexcept>

namespace logic::camera
{

core::BoxF CameraSystem::GetRenderBoundary() const
{
	return m_position + m_size;
}

void CameraSystem::RegisterCameraControl(core::EntityId i_entityId)
{
	m_authorizedEntityIds.emplace(i_entityId);
}

void CameraSystem::DeregisterCameraControl(core::EntityId i_entityId)
{
	if (m_authorizedEntityIds.contains(i_entityId))
	{
		m_authorizedEntityIds.erase(m_authorizedEntityIds.find(i_entityId));
	}
	else
	{
		DEBUG(throw_with_nested(std::runtime_error("Deregister unregistered entityId!")));
	}
}

void CameraSystem::TrySetPosition(core::EntityId i_callerId, core::Vector2F i_position)
{
	if (m_authorizedEntityIds.contains(i_callerId))
	{
		SetPosition(i_position);
	}
}

void CameraSystem::TrySetCentralPosition(core::EntityId i_callerId, core::Vector2F i_centralPosition)
{
	if (m_authorizedEntityIds.contains(i_callerId))
	{
		SetCentralPosition(i_centralPosition);
	}
}

void CameraSystem::TrySetAbsoluteBoundary(core::EntityId i_callerId, core::BoxF i_absoluteBoundary)
{
	if (m_authorizedEntityIds.contains(i_callerId))
	{
		SetAbsoluteBoundary(i_absoluteBoundary);
	}
}

void CameraSystem::TrySetRelativeBoundary(core::EntityId i_callerId, core::BoxF i_relativeBoundary)
{
	if (m_authorizedEntityIds.contains(i_callerId))
	{
		SetRelativeBoundary(i_relativeBoundary);
	}
}

void CameraSystem::SetPosition(core::Vector2F i_position)
{
	m_position = i_position;
}

void CameraSystem::SetCentralPosition(core::Vector2F i_centralPosition)
{
	m_position = core::Vector2F
	{
		i_centralPosition.x - m_size.width / 2,
		i_centralPosition.y - m_size.height / 2
	};
}

void CameraSystem::SetAbsoluteBoundary(core::BoxF i_absoluteBoundary)
{
	m_size = core::ToSize(i_absoluteBoundary);
	m_position = core::Vector2F();
}

void CameraSystem::SetRelativeBoundary(core::BoxF i_relativeBoundary)
{
	m_size = core::ToSize(i_relativeBoundary);
}

} // namespace logic::camera