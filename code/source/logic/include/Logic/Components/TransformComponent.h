#pragma once
#include "PositionSetterComponent.h"
#include <memory>
#include <vector>

namespace logic
{

/// <summary>
/// Only transform should have getter position
/// </summary>
class TransformComponent final: public PositionSetterComponent
{
public:
	TransformComponent(const core::Vector2F i_position = core::Vector2F());

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const;
	void Register() override;
	void Deregister() override;

private:
	core::Vector2F m_position;
};


} // namespace logic