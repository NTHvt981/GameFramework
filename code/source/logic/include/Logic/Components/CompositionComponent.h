#pragma once
#include "IComponent.h"
#include <memory>
#include <vector>

namespace logic
{

/// <summary>
/// Contain multiple components, return position of the first
/// </summary>
class CompositionComponent final: public IComponent
{
public:
	CompositionComponent(std::initializer_list<std::shared_ptr<IComponent>> i_children);

	// Inherited via IComponent
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override;
	void Deregister() override;

private:
	std::vector<std::shared_ptr<IComponent>> m_children;
};


} // namespace logic