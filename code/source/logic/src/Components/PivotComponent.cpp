#include "Logic/Components/PivotComponent.h"
#include "Core/Helpers/Vector2Helper.h"

namespace logic
{

PivotComponent::PivotComponent(std::shared_ptr<PositionSetterComponent> i_child, core::Vector2F i_pivot)
	: m_child(i_child)
	, m_pivot(i_pivot)
{
}

void PivotComponent::SetPosition(const core::Vector2F& i_position)
{
	m_child->SetPosition(i_position + m_pivot);
}

void PivotComponent::Register()
{
	m_child->Register();
}

void PivotComponent::Deregister()
{
	m_child->Deregister();
}

} // namespace logic