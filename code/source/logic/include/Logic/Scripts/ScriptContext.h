#pragma once
#include "IScriptContext.h"

namespace logic
{

class ScriptContext final: public IScriptContext
{
public:
	ScriptContext(
		core::Ref<core::logic::IGameClock> i_gameClock,
		core::Ref<IEntitiesFactory> i_entitesFactory,
		core::Ref<EntitiesManager> i_entitiesManager
	);
	// Inherited via IScriptContext
	core::Ref<core::logic::IGameClock> GetGameClock() override;
	core::Ref<IEntitiesFactory> GetEntitiesFactory() override;
	core::Ref<EntitiesManager> GetEntitiesManager() override;

private:
	core::Ref<core::logic::IGameClock> m_gameClock;
	core::Ref<IEntitiesFactory> m_entitiesFactory;
	core::Ref<EntitiesManager> m_entitiesManager;
};

} // namespace logic