#pragma once
#include "Logic/Entities/Entity.h"

namespace logic
{

Entity::Entity(core::EntityId i_id)
	: m_id(i_id)
{
}

core::EntityId Entity::GetId() const
{
	return m_id;
}

void Entity::InsertComponent(core::ComponentKey i_componentKey, std::shared_ptr<IComponent> i_component)
{
	m_components.emplace(i_componentKey, i_component);
}

bool Entity::HasComponent(core::ComponentKey i_componentKey) const
{
	return m_components.contains(i_componentKey);
}

void Entity::Register()
{
	if (isRegistered)
	{
		return;
	}
	isRegistered = true;

	for (auto& [key, component] : m_components)
	{
		component->Register();
	}
}

void Entity::Deregister()
{
	if (!isRegistered)
	{
		return;
	}
	isRegistered = false;

	for (auto& [key, component] : m_components)
	{
		component->Register();
	}
}

std::shared_ptr<IComponent> Entity::GetComponent(core::ComponentKey i_componentKey) const
{
	return m_components.at(i_componentKey);
}

} // namespace logic
