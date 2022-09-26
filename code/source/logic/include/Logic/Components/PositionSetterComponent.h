#pragma once
#include "Component.h"
#include "Core/DataTypes/Vector2.h"

namespace logic
{

/// <summary>
/// Any component use position (sprite, animation, kinematic) need to inherit this
/// </summary>
class PositionSetterComponent: public Component
{
public:
	virtual void SetPosition(const core::Vector2F& i_position) = 0;
};

} // namespace logic