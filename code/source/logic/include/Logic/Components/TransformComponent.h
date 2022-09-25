#pragma once
#include "Component.h"
#include <memory>
#include <vector>

namespace logic
{

/// <summary>
/// A simple component with position, no child
/// </summary>
class TransformComponent final: public Component
{
public:
	TransformComponent(const core::Vector2F i_position = core::Vector2F());

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

private:
	core::Vector2F m_position;
};


} // namespace logic