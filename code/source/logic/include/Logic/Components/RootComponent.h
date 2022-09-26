#pragma once
#include "Component.h"
#include "Core/DataTypes/String.h"
#include <memory>
#include <map>

namespace logic
{

/// <summary>
/// Special component, every enity must have 1 RootComponent
/// this contain mapping of string keys and component
/// use for checking (if have healthComponent...)
/// </summary>
class RootComponent final: public Component
{
public:
	RootComponent(std::map<core::String, std::shared_ptr<Component>> i_children);

	// Inherited via Component
	void Register() override;
	void Deregister() override;

	void InsertComponent(const core::String i_componentKey, std::shared_ptr<Component> i_component);
	void RemoveComponent(const core::String i_componentKey);
	bool ContainComponent(const core::String i_componentKey);
	std::weak_ptr<Component> GetComponent(const core::String i_componentKey);

private:
	std::map<core::String, std::shared_ptr<Component>> m_children;
};


} // namespace logic