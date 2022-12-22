#pragma once
#include "IComponent.h"
#include "Core/DataTypes/Vector2.h"

namespace logic
{

class ITransformComponent: public IComponent
{
public:
	virtual void SetPosition(core::Vector2F i_position) = 0;
	virtual core::Vector2F GetPosition() const = 0;
};

} // namespace logic