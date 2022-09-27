#include "Logic/Components/TransformComponent.h"

namespace logic
{

TransformComponent::TransformComponent(const core::Vector2F i_position)
	: m_position(i_position)
{
}

void TransformComponent::SetPosition(const core::Vector2F& i_position)
{
	m_position = i_position;
}

core::Vector2F TransformComponent::GetPosition() const
{
	return m_position;
}

} // namespace logic