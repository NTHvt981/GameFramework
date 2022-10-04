#include "Logic/Scripts/ScriptContext.h"
#include "Core/GameClock/IGameClock.h"
#include "Logic/Factories/IEntitiesFactory.h"
#include "Logic/Managers/EntitiesManager.h"

namespace logic
{

ScriptContext::ScriptContext(
	std::shared_ptr<core::logic::IGameClock> i_gameClock, 
	std::shared_ptr<IEntitiesFactory> i_entitiesFactory,
	std::shared_ptr<EntitiesManager> i_entitiesManager)
	: m_gameClock(i_gameClock)
	, m_entitiesFactory(i_entitiesFactory)
	, m_entitiesManager(i_entitiesManager)
{
}

std::shared_ptr<core::logic::IGameClock> ScriptContext::GetGameClock()
{
	return m_gameClock;
}

std::shared_ptr<IEntitiesFactory> ScriptContext::GetEntitiesFactory()
{
	return m_entitiesFactory;
}

std::shared_ptr<EntitiesManager> ScriptContext::GetEntitiesManager()
{
	return m_entitiesManager;
}

} // namespace logic