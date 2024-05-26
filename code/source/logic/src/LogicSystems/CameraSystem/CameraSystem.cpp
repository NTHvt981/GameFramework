#include "Logic/LogicSystems/CameraSystem/CameraSystem.h"
#include "Core/Helpers/SizeBoxHelper.h"
#include "Core/Macros/Macros.h"
#include <stdexcept>

namespace logic::camera
{

CameraSystem::CameraSystem(
	std::shared_ptr<core::IViewportGraphicAPI> i_viewportGraphicAPI)
	: m_viewportGraphicAPI(i_viewportGraphicAPI)
	, m_authorizedEntityId(-1)
{
}

void CameraSystem::RegisterCameraControl(core::EntityId i_entityId)
{
	m_authorizedEntityId = i_entityId;
}

void CameraSystem::DeregisterCameraControl(core::EntityId i_entityId)
{
	if (m_authorizedEntityId == i_entityId)
	{
		m_authorizedEntityId = -1;
	}
}

void CameraSystem::TrySetPosition(core::EntityId i_callerId, core::Vector2F i_position)
{
	if (m_authorizedEntityId == i_callerId)
	{
		SetPosition(i_position);
	}
}

void CameraSystem::TrySetCentralPosition(core::EntityId i_callerId, core::Vector2F i_centralPosition)
{
	if (m_authorizedEntityId == i_callerId)
	{
		SetCentralPosition(i_centralPosition);
	}
}

void CameraSystem::TrySetAbsoluteBoundary(core::EntityId i_callerId, core::BoxF i_absoluteBoundary)
{
	if (m_authorizedEntityId == i_callerId)
	{
		SetAbsoluteBoundary(i_absoluteBoundary);
	}
}

void CameraSystem::TrySetSize(core::EntityId i_callerId, core::SizeF i_size)
{
	if (m_authorizedEntityId == i_callerId)
	{
		SetSize(i_size);
	}
}

void CameraSystem::SetPosition(core::Vector2F i_position)
{
	m_position = i_position;
	m_viewportGraphicAPI->SetViewportPosition(m_position);
}

void CameraSystem::SetCentralPosition(core::Vector2F i_centralPosition)
{
	m_position = core::Vector2F
	{
		i_centralPosition.x - m_size.width / 2,
		i_centralPosition.y - m_size.height / 2
	};
	m_viewportGraphicAPI->SetViewportPosition(m_position);
}

void CameraSystem::SetAbsoluteBoundary(core::BoxF i_absoluteBoundary)
{
	m_size = core::ToSize(i_absoluteBoundary);
	m_position = core::Vector2F{ 0,0 };
	m_viewportGraphicAPI->SetViewportSize(m_size);
	m_viewportGraphicAPI->SetViewportPosition(m_position);
}

void CameraSystem::SetSize(core::SizeF i_size)
{
	m_size = i_size;
	m_viewportGraphicAPI->SetViewportSize(m_size);
}

} // namespace logic::camera