#include "Logic/LogicSystems/CameraSystem/CameraSystem.h"
#include "Core/Helpers/SizeBoxHelper.h"

namespace logic::camera
{

core::BoxF CameraSystem::GetRenderBoundary() const
{
	return m_position + m_size;
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