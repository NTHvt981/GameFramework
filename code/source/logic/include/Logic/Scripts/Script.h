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
	virtual void OnCreate(core::Ref<IScriptContext> i_scriptContext) {};
	virtual void OnDestroy() = 0;
	virtual void OnPause() {};
	virtual void OnResume() {};
	virtual void OnUpdate(const core::Duration& dt) {};
	virtual void OnFixedUpdate(const core::Duration& dt) {};
	virtual void OnRender(const core::Duration& dt) {};

	core::ScriptState scriptState = core::ScriptState::Created;
	signals::Callback<std::unique_ptr<Script>> requestAddScriptToManagerCallback;

	using ID = uint64_t;
	ID id = 0;
};

} // namespace logic