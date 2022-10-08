#pragma once
#include "ICameraSystem.h"
#include "Core/DataTypes/Size.h"
#include "Core/Identifiers/EntityId.h"
#include "GraphicSystem/API/IViewportGraphicAPI.h"
#include <memory>

namespace logic::camera
{

class CameraSystem final : public ICameraSystem
{
public:
	CameraSystem(std::shared_ptr<graphics::IViewportGraphicAPI> i_viewportGraphicAPI);

	// Inherited via ICameraSystem
	void RegisterCameraControl(core::EntityId i_entityId) override;
	void DeregisterCameraControl(core::EntityId i_entityId) override;

	void TrySetPosition(core::EntityId i_callerId, core::Vector2F i_position) override;
	void TrySetCentralPosition(core::EntityId i_callerId, core::Vector2F i_centralPosition) override;
	void TrySetAbsoluteBoundary(core::EntityId i_callerId, core::BoxF i_absoluteBoundary) override;
	void TrySetSize(core::EntityId i_callerId, core::SizeF i_size) override;

	void SetPosition(core::Vector2F i_position) override;
	void SetCentralPosition(core::Vector2F i_centralPosition) override;
	void SetAbsoluteBoundary(core::BoxF i_absoluteBoundary) override;
	void SetSize(core::SizeF i_size) override;
private:
	std::shared_ptr<graphics::IViewportGraphicAPI> m_viewportGraphicAPI;
	core::EntityId m_authorizedEntityId;
	core::SizeF m_size = core::SizeF{ 0, 0 };
	core::Vector2F m_position = core::Vector2F{ 0, 0 };
};

} // namespace logic::camera