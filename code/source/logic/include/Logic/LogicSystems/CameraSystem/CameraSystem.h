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
	void TrySetRelativeBoundary(core::EntityId i_callerId, core::BoxF i_relativeBoundary) override;

	void SetPosition(core::Vector2F i_position) override;
	void SetCentralPosition(core::Vector2F i_centralPosition) override;
	void SetAbsoluteBoundary(core::BoxF i_absoluteBoundary) override;
	void SetRelativeBoundary(core::BoxF i_relativeBoundary) override;
private:
	std::set<core::EntityId> m_authorizedEntityIds;
	core::SizeF m_size;
	core::Vector2F m_position;
};

} // namespace logic::camera