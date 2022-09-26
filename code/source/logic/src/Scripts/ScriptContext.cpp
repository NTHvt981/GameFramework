#include "Logic/Scripts/ScriptContext.h"

namespace logic
{

ScriptContext::ScriptContext(
	std::shared_ptr<core::logic::IGameClock> i_gameClock, 
	std::shared_ptr<IEntityFactory> i_entityFactory)
	: m_gameClock(i_gameClock)
	, m_entityFactory(i_entityFactory)
{
}

std::shared_ptr<core::logic::IGameClock> ScriptContext::GetGameClock()
{
	return m_gameClock;
}

std::shared_ptr<IEntityFactory> ScriptContext::GetEntityFactory()
{
	return m_entityFactory;
}

} // namespace logic