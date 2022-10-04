#pragma once
#include "IScriptContext.h"

namespace logic
{

class ScriptContext final: public IScriptContext
{
public:
	ScriptContext(
		std::shared_ptr<core::logic::IGameClock> i_gameClock,
		std::shared_ptr<IEntitiesFactory> i_entitesFactory,
		std::shared_ptr<EntitiesManager> i_entitiesManager
	);
	// Inherited via IScriptContext
	std::shared_ptr<core::logic::IGameClock> GetGameClock() override;
	std::shared_ptr<IEntitiesFactory> GetEntitiesFactory() override;
	std::shared_ptr<EntitiesManager> GetEntitiesManager() override;

private:
	std::shared_ptr<core::logic::IGameClock> m_gameClock;
	std::shared_ptr<IEntitiesFactory> m_entitiesFactory;
	std::shared_ptr<EntitiesManager> m_entitiesManager;
};

} // namespace logic