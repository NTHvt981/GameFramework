#pragma once
#include "Component.h"
#include <memory>
#include <vector>

namespace logic
{

/// <summary>
/// Contain multiple components, return position of the first
/// </summary>
class CompositionComponent final: public Component
{
public:
	CompositionComponent(std::initializer_list<std::shared_ptr<Component>> i_children);

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

private:
	std::vector<std::shared_ptr<Component>> m_children;
};


} // namespace logic