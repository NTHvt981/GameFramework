#pragma once
#include "IScriptContext.h"

namespace logic
{

class Script
{
public:
	virtual void Initialize(std::shared_ptr<IScriptContext> i_scriptContext) = 0;
	virtual void Shutdown() = 0;
};

} // namespace logic