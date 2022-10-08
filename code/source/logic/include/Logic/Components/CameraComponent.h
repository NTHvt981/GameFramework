#pragma once
#include "ITransformComponent.h"
#include "Logic/LogicSystems/CameraSystem/IEntityCameraAPI.h"
#include "Core/DataTypes/Ref.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_cameraComponentKey = "CameraComponent";

class CameraComponent final : public ITransformComponent
{
public:
	CameraComponent(
		std::shared_ptr<camera::IEntityCameraAPI> i_cameraAPI,
		core::EntityId i_entityId
	);

	// Inherited via Component
	void Register() override;
	void Deregister() override;
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;

	void SetCameraPosition(core::Vector2F i_position);
	void SetCameraSize(core::SizeF i_size);
	void SetCameraCentralPosition(core::Vector2F i_position);

private:
	core::Vector2F m_position;
	core::Ref<camera::IEntityCameraAPI> m_cameraAPI;
	const core::EntityId m_entityId;
};

} // namespace logic