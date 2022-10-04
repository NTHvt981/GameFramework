#pragma once
#include "IScriptContext.h"
#include "Core/DataTypes/Duration.h"

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
};

} // namespace logic