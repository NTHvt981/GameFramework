#pragma once
#include "IEntityCameraAPI.h"
#include "Core/DataTypes/Vector2.h"

namespace logic::camera
{

class ICameraSystem : public IEntityCameraAPI
{
public:
	virtual void SetPosition(core::Vector2F i_position) = 0;
	virtual void SetCentralPosition(core::Vector2F i_centralPosition) = 0;
	virtual void SetAbsoluteBoundary(core::BoxF i_absoluteBoundary) = 0;
	virtual void SetSize(core::SizeF i_size) = 0;
};

} // namespace logic::camera