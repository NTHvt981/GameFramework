#pragma once
#include "ICameraSystem.h"
#include "Core/DataTypes/Size.h"

namespace logic::camera
{

class CameraSystem final : public ICameraSystem
{
public:
	core::BoxF GetRenderBoundary() const override;

	// Inherited via ICameraSystem
	void SetPosition(core::Vector2F i_position) override;
	void SetCentralPosition(core::Vector2F i_centralPosition) override;
	void SetAbsoluteBoundary(core::BoxF i_absoluteBoundary) override;
	void SetRelativeBoundary(core::BoxF i_relativeBoundary) override;

private:
	core::SizeF m_size;
	core::Vector2F m_position;
};

} // namespace logic::camera