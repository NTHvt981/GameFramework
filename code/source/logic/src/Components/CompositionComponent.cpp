#include "Logic/Components/CompositionComponent.h"
#include <assert.h>

namespace logic
{

CompositionComponent::CompositionComponent(std::initializer_list<std::shared_ptr<Component>> i_children)
	: m_children(i_children)
{
	assert(i_children.size() > 0);
}

void CompositionComponent::SetPosition(const core::Vector2F& i_position)
{
	for (std::shared_ptr<Component> child : m_children)
	{
		child->SetPosition(i_position);
	}
}

core::Vector2F CompositionComponent::GetPosition() const
{
	return m_children[0]->GetPosition();
}

void CompositionComponent::Register()
{
	for (std::shared_ptr<Component> child : m_children)
	{
		child->Register();
	}
}

void CompositionComponent::Deregister()
{
	for (std::shared_ptr<Component> child : m_children)
	{
		child->Deregister();
	}
}

} // namespace logic