#pragma once
#include "Logic/Scripts/Script.h"

namespace logic
{

Script::Script(
	core::Ref<Entity> i_entity, 
	core::Ref<IScriptContext> i_scriptContext)
	: m_entity(i_entity)
	, m_scriptContext(i_scriptContext)
{
}

} // namespace logic