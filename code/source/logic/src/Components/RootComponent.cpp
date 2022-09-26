#pragma once
#include "Logic/Components/RootComponent.h"

namespace logic
{

RootComponent::RootComponent(std::map<core::String, std::shared_ptr<Component>> i_children)
	: m_children(i_children)
{
}

void RootComponent::Register()
{
	for (auto& [componentId, component] : m_children)
	{
		component->Register();
	}
}

void RootComponent::Deregister()
{
	for (auto& [componentId, component] : m_children)
	{
		component->Deregister();
	}
}

void RootComponent::InsertComponent(const core::String i_componentKey, std::shared_ptr<Component> i_component)
{
	m_children.try_emplace(i_componentKey, i_component);
}

void RootComponent::RemoveComponent(const core::String i_componentKey)
{
	m_children.erase(i_componentKey);
}

bool RootComponent::ContainComponent(const core::String i_componentKey)
{
	return m_children.contains(i_componentKey);
}

std::weak_ptr<Component> RootComponent::GetComponent(const core::String i_componentKey)
{
	return m_children.at(i_componentKey);
}

} // namespace logic