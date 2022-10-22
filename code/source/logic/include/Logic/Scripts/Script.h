#pragma once
#include "IScriptContext.h"
#include "Core/DataTypes/Duration.h"
#include "Core/Identifiers/ScriptState.h"
#include "Core/Signals/Signal.h"
#include "Core/Signals/Connection.h"
#include "Core/DataTypes/Ref.h"
#include "Core/Identifiers/ComponentKey.h"
#include "Logic/Entities/Entity.h"

namespace logic
{

class Script
{
public:
	Script(
		core::Ref<Entity> i_entity, 
		core::Ref<IScriptContext> i_scriptContext
	);
	virtual void OnCreate() {};
	virtual void OnDestroy() {};
	virtual void OnPause() {};
	virtual void OnResume() {};
	virtual void OnUpdate(const core::Duration& dt) {};
	virtual void OnFixedUpdate(const core::Duration& dt) {};
	virtual void OnRender(const core::Duration& dt) {};

	core::ScriptState scriptState = core::ScriptState::Created;
	signals::Callback<core::Ref<Script>> requestAddScriptToManagerCallback;

protected:
	template<class T>
	core::Ref<T> GetComponent(core::ComponentKey i_componentKey) const
	{
		return m_entity->GetComponent<T>(i_componentKey);
	}

	core::Ref<Entity> m_entity;
	core::Ref<IScriptContext> m_scriptContext;
};

} // namespace logic