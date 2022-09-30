#pragma once
#include "ITransformComponent.h"
#include <memory>

namespace logic
{

static constexpr core::ComponentKey sk_pivotComponentKey = "PivotComponent";

class PivotComponent final: public ITransformComponent
{
public:
	PivotComponent(std::shared_ptr<ITransformComponent> i_child);

	// Inherited via Component
	void SetPosition(core::Vector2F i_position) override;
	core::Vector2F GetPosition() const override;
	void Register() override {};
	void Deregister() override {};

	void SetPivot(core::Vector2F i_pivot);
	core::Vector2F GetPivot() const;

private:
	std::shared_ptr<ITransformComponent> m_child;
	core::Vector2F m_pivot;
};

} // namespace logic