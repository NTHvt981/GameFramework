#pragma once
#include "Logic/Components/IComponent.h"
#include "Core/Identifiers/EntityId.h"
#include "Core/Identifiers/ComponentKey.h"
#include "Core/Signals/Callback.h"
#include "Core/Signals/Signal.h"
#include "Core/Signals/Connection.h"
#include <memory>
#include <map>
#include <type_traits>
#include <initializer_list>

namespace logic
{

class Entity
{
public:
	Entity(core::EntityId i_id);
	core::EntityId GetId() const;
	void InsertComponent(core::ComponentKey i_componentKey, std::shared_ptr<IComponent> i_component);
	bool HasComponent(core::ComponentKey i_componentKey) const;
	bool HasAnyComponents(std::initializer_list<core::ComponentKey> i_componentKeys) const;
	bool HasAllComponents(std::initializer_list<core::ComponentKey> i_componentKeys) const;
	std::shared_ptr<IComponent> GetComponent(core::ComponentKey i_componentKey) const;

	template<class T>
	std::shared_ptr<T> GetComponent(core::ComponentKey i_componentKey) const
	{
		static_assert(std::is_base_of<IComponent, T>::value);
		return std::static_pointer_cast<T>(m_components.at(i_componentKey));
	}

	void Register();
	void Deregister();
	void SetDeregisterCallback(const signals::Callback<>& i_callback);

private:
	const core::EntityId m_id;
	std::map<core::ComponentKey, std::shared_ptr<IComponent>> m_components;
	signals::Signal<> sig_onDeregistered;
	signals::Connection<> m_onDeregisteredCon;
	bool isRegistered = false;
};

} // namespace logic
