#include "Logic/Scripts/ScriptContext.h"
#include "Core/GameClock/IGameClock.h"
#include "Logic/Factories/IEntitiesFactory.h"
#include "Logic/Managers/EntitiesManager.h"

namespace logic
{

ScriptContext::ScriptContext(
	core::Ref<core::logic::IGameClock> i_gameClock,
	core::Ref<IEntitiesFactory> i_entitiesFactory,
	core::Ref<EntitiesManager> i_entitiesManager)
	: m_gameClock(i_gameClock)
	, m_entitiesFactory(i_entitiesFactory)
	, m_entitiesManager(i_entitiesManager)
{
}

core::Ref<core::logic::IGameClock> ScriptContext::GetGameClock()
{
	return m_gameClock;
}

core::Ref<IEntitiesFactory> ScriptContext::GetEntitiesFactory()
{
	return m_entitiesFactory;
}

core::Ref<EntitiesManager> ScriptContext::GetEntitiesManager()
{
	return m_entitiesManager;
}

} // namespace logic