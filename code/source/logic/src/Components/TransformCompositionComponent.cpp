#include "Logic/Components/TransformCompositionComponent.h"
#include <assert.h>

namespace logic
{

TransformCompositionComponent::TransformCompositionComponent(std::initializer_list<std::shared_ptr<ITransformComponent>> i_children)
	: m_children(i_children)
{
	assert(i_children.size() > 0);
}

void TransformCompositionComponent::SetPosition(core::Vector2F i_position)
{
	for (std::shared_ptr<ITransformComponent> child : m_children)
	{
		child->SetPosition(i_position);
	}
}

void TransformCompositionComponent::InsertComponent(std::shared_ptr<ITransformComponent> i_component)
{
	m_children.push_back(i_component);
}

void TransformCompositionComponent::RemoveComponent(std::shared_ptr<ITransformComponent> i_component)
{
	m_children.remove(i_component);
}

core::Vector2F TransformCompositionComponent::GetPosition() const
{
	return m_children.front()->GetPosition();
}

} // namespace logic