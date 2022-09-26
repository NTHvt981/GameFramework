#pragma once
#include "IScriptContext.h"

namespace logic
{

class ScriptContext final: public IScriptContext
{
public:
	ScriptContext(
		std::shared_ptr<core::logic::IGameClock> i_gameClock,
		std::shared_ptr<IEntityFactory> i_entityFactory
	);
	// Inherited via IScriptContext
	std::shared_ptr<core::logic::IGameClock> GetGameClock() override;
	std::shared_ptr<IEntityFactory> GetEntityFactory() override;

private:
	std::shared_ptr<core::logic::IGameClock> m_gameClock;
	std::shared_ptr<IEntityFactory> m_entityFactory;
};

} // namespace logic