#pragma once
#include "PositionSetterComponent.h"
#include <memory>
#include <vector>

namespace logic
{

/// <summary>
/// Contain multiple components
/// </summary>
class CompositionComponent final: public PositionSetterComponent
{
public:
	CompositionComponent(std::initializer_list<std::shared_ptr<PositionSetterComponent>> i_children);

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	void Register() override {};
	void Deregister() override {};

	void InsertComponent(std::shared_ptr<PositionSetterComponent> i_component);

private:
	std::vector<std::shared_ptr<PositionSetterComponent>> m_children;
};


} // namespace logic