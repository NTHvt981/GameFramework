#include "Logic/Components/PivotComponent.h"
#include "Core/Helpers/Vector2Helper.h"

namespace logic
{

PivotComponent::PivotComponent(std::shared_ptr<ITransformComponent> i_child, const core::Vector2F i_pivot)
	: m_child(i_child)
	, m_pivot(i_pivot)
{
}

void PivotComponent::SetPosition(const core::Vector2F& i_position)
{
	m_child->SetPosition(i_position + m_pivot);
}

core::Vector2F PivotComponent::GetPosition() const
{
	return m_child->GetPosition() - m_pivot;
}

} // namespace logic