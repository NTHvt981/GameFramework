#pragma once
#include "Logic/Components/IComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Identifiers/ComponentKey.h"
#include <memory>
#include <map>
#include <type_traits>

namespace logic
{

class Entity
{
public:
	Entity(core::EntityId i_id);
	void InsertComponent(core::ComponentKey i_componentKey, std::shared_ptr<IComponent> i_component);
	bool HasComponent(core::ComponentKey i_componentKey) const;
	std::shared_ptr<IComponent> GetComponent(core::ComponentKey i_componentKey) const;

	template<class T>
	std::shared_ptr<T> GetComponent(core::ComponentKey i_componentKey) const
	{
		static_assert(std::is_base_of<IComponent, T>::value);
		return std::static_pointer_cast<T>(m_components.at(i_componentKey));
	}

	void Register();
	void Deregister();

private:
	const core::EntityId m_id;
	std::map<core::ComponentKey, std::shared_ptr<IComponent>> m_components;

	bool isRegistered = false;
};

} // namespace logic
