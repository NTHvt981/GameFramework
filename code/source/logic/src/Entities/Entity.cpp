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

bool Entity::HasAnyComponents(std::initializer_list<core::ComponentKey> i_componentKeys) const
{
	for (const core::ComponentKey& componentKey: i_componentKeys)
	{
		if (HasComponent(componentKey))
		{
			return true;
		}
	}
	return false;
}

bool Entity::HasAllComponents(std::initializer_list<core::ComponentKey> i_componentKeys) const
{
	for (const core::ComponentKey& componentKey: i_componentKeys)
	{
		if (!HasComponent(componentKey))
		{
			return false;
		}
	}
	return true;
}

void Entity::Register()
{
	if (m_isRegistered)
	{
		return;
	}
	m_isRegistered = true;

	for (auto& [key, component] : m_components)
	{
		component->Register();
	}
}

void Entity::Deregister()
{
	if (!m_isRegistered)
	{
		return;
	}
	m_isRegistered = false;

	for (auto& [key, component] : m_components)
	{
		component->Deregister();
	}
}

void Entity::SetDeregisterCallback(const signals::Callback<>& i_callback)
{
	m_onDeregisteredCon = sig_onDeregistered.Connect(i_callback);
}

core::Ref<IComponent> Entity::GetComponentRef(core::ComponentKey i_componentKey) const
{
	return core::Ref<IComponent>(m_components.at(i_componentKey));
}

std::shared_ptr<IComponent> Entity::GetComponent(core::ComponentKey i_componentKey) const
{
	return m_components.at(i_componentKey);
}

} // namespace logic
