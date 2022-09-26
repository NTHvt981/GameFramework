#include "Logic/Components/CompositionComponent.h"
#include <assert.h>

namespace logic
{

CompositionComponent::CompositionComponent(std::initializer_list<std::shared_ptr<PositionSetterComponent>> i_children)
	: m_children(i_children)
{
	assert(i_children.size() > 0);
}

void CompositionComponent::SetPosition(const core::Vector2F& i_position)
{
	for (std::shared_ptr<PositionSetterComponent> child : m_children)
	{
		child->SetPosition(i_position);
	}
}

void CompositionComponent::InsertComponent(std::shared_ptr<PositionSetterComponent> i_component)
{
	m_children.push_back(i_component);
}

} // namespace logic