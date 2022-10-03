#pragma once
#include "IScriptContext.h"

namespace logic
{

class ScriptContext final: public IScriptContext
{
public:
	ScriptContext(
		std::shared_ptr<core::logic::IGameClock> i_gameClock,
		std::shared_ptr<IEntitiesFactory> i_entityFactory
	);
	// Inherited via IScriptContext
	std::shared_ptr<core::logic::IGameClock> GetGameClock() override;
	std::shared_ptr<IEntitiesFactory> GetEntityFactory() override;
	std::shared_ptr<Entities> GetEntities() override;

private:
	std::shared_ptr<core::logic::IGameClock> m_gameClock;
	std::shared_ptr<IEntitiesFactory> m_entityFactory;
	std::shared_ptr<Entities> m_entities;
};

} // namespace logic