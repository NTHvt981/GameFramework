#pragma once
#include "ICameraSystem.h"
#include "Core/DataTypes/Size.h"
#include "Core/Identifiers/EntityId.h"
#include <set>

namespace logic::camera
{

class CameraSystem final : public ICameraSystem
{
public:
	core::BoxF GetRenderBoundary() const override;

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
	core::EntityId m_authorizedEntityId;
	core::SizeF m_size;
	core::Vector2F m_position;
};

} // namespace logic::camera