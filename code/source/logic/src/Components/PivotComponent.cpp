#include "Logic/Components/PivotComponent.h"
#include "Core/Helpers/Vector2Helper.h"

namespace logic
{

PivotComponent::PivotComponent(std::shared_ptr<ITransformComponent> i_child)
	: m_child(i_child)
{
}

void PivotComponent::SetPosition(core::Vector2F i_position)
{
	m_child->SetPosition(i_position + m_pivot);
}

core::Vector2F PivotComponent::GetPosition() const
{
	return m_child->GetPosition() - m_pivot;
}

void PivotComponent::SetPivot(core::Vector2F i_pivot)
{
	m_pivot = i_pivot;
}

core::Vector2F PivotComponent::GetPivot() const
{
	return m_pivot;
}

} // namespace logic