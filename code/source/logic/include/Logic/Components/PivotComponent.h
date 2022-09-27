#pragma once
#include "ITransformComponent.h"
#include <memory>

namespace logic
{

/// <summary>
/// A component with 1 child, 1 pivot (relative position)
/// </summary>
class PivotComponent final: public ITransformComponent
{
public:
	PivotComponent(
		std::shared_ptr<ITransformComponent> i_child,
		const core::Vector2F i_pivot = core::Vector2F()
	);

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override {};
	void Deregister() override {};

private:
	std::shared_ptr<ITransformComponent> m_child;
	core::Vector2F m_pivot;
};

} // namespace logic