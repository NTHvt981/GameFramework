#pragma once
#include "Core/DataTypes/Vector2.h"
#include "Core/DataTypes/Box.h"
#include "Core/DataTypes/Size.h"
#include "Core/Identifiers/EntityId.h"

namespace logic::camera
{

class IEntityCameraAPI
{
public:
	virtual void RegisterCameraControl(core::EntityId i_entityId) = 0;
	virtual void DeregisterCameraControl(core::EntityId i_entityId) = 0;
	virtual void TrySetPosition(core::EntityId i_callerId, core::Vector2F i_position) = 0;
	virtual void TrySetCentralPosition(core::EntityId i_callerId, core::Vector2F i_centralPosition) = 0;
	virtual void TrySetAbsoluteBoundary(core::EntityId i_callerId, core::BoxF i_absoluteBoundary) = 0;
	virtual void TrySetSize(core::EntityId i_callerId, core::SizeF i_size) = 0;
};

} // namespace logic::camera