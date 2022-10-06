#pragma once
#include "IScriptContext.h"
#include "Core/DataTypes/Duration.h"
#include "Core/Identifiers/ScriptState.h"
#include "Core/Signals/Signal.h"
#include "Core/Signals/Connection.h"
#include "Core/DataTypes/Ref.h"

namespace logic
{

class Script
{
public:
	virtual void OnCreate(std::shared_ptr<IScriptContext> i_scriptContext) = 0;
	virtual void OnDestroy() = 0;
	virtual void OnPause() {};
	virtual void OnResume() {};
	virtual void OnUpdate(const core::Duration& dt) {};
	virtual void OnFixedUpdate(const core::Duration& dt) {};
	virtual void OnRender(const core::Duration& dt) {};

	core::ScriptState scriptState = core::ScriptState::Created;
	signals::Connection<core::Ref<Script>> requestCreateScriptCon;
	signals::Signal<core::Ref<Script>> sig_requestCreateScript;
};

} // namespace logic