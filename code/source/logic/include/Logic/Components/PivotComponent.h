#pragma once
#include "PositionSetterComponent.h"
#include <memory>

namespace logic
{

/// <summary>
/// A component with 1 child, 1 pivot (relative position)
/// </summary>
class PivotComponent final: public PositionSetterComponent
{
public:
	PivotComponent(
		std::shared_ptr<PositionSetterComponent> i_child,
		core::Vector2F i_pivot = core::Vector2F()
	);

	// Inherited via Component
	void SetPosition(const core::Vector2F& i_position) override;
	void Register() override;
	void Deregister() override;

private:
	std::shared_ptr<PositionSetterComponent> m_child;
	core::Vector2F m_pivot;
};

} // namespace logic